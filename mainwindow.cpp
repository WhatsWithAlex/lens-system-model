
#include <QString>
#include "model.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lenses_states(5)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    // initialize lenses select combo box
    for (int i = 1; i <= 5; ++i) {
        ui->lensesSelectComboBox->addItem(QString::number(i));
    }
    ui->lensesSelectComboBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//          Signals         //
void MainWindow::on_menuCalculateButton_clicked()
{
    float object_x = ui->objectXInput->text().toFloat();
    float object_size = ui->objectSizeInput->text().toFloat();
    ObjectOrientation object_orientation;
    if (ui->objectOrientationRBUp->isChecked())
        object_orientation = ObjectOrientation::up;
    else
        object_orientation = ObjectOrientation::down;

    int current_lens_index = ui->lensesSelectComboBox->currentIndex();
    saveLensState(current_lens_index);

    model.set_object(Object(object_x, object_size, object_orientation));
    for (int i = 0; i < 5; ++i)
    {
        if (lenses_states[i].is_focal_length_set) {
            model.setLens(
                i,
                Lens(
                    lenses_states[i].x,
                    lenses_states[i].focal_length,
                    lenses_states[i].is_active
                )
            );
        } else {
            model.setLens(
                i,
                Lens(
                    lenses_states[i].x,
                    lenses_states[i].r1,
                    lenses_states[i].r2,
                    lenses_states[i].is_active
                )
            );
        }
    }

    model.calculate();
    Image result_image = model.get_image();

    showImageStats(result_image);
}

void MainWindow::on_lensesSelectComboBox_currentIndexChanged(int index)
{
    saveLensState(prev_lens_index);
    showLensState(index);
    prev_lens_index = index;
}

void MainWindow::on_lensesSettingRBFocalLen_toggled(bool checked)
{
    int current_lens_index = ui->lensesSelectComboBox->currentIndex();
    saveLensState(current_lens_index);
    showLensState(current_lens_index);
}

void MainWindow::on_lensesSettingR1Input_editingFinished()
{
    int current_lens_index = ui->lensesSelectComboBox->currentIndex();
    lenses_states[current_lens_index].r1 = ui->lensesSettingR1Input->text().toFloat();
    saveLensState(current_lens_index);
    showLensState(current_lens_index);
}

void MainWindow::on_lensesSettingR2Input_editingFinished()
{
    int current_lens_index = ui->lensesSelectComboBox->currentIndex();
    lenses_states[current_lens_index].r2 = ui->lensesSettingR2Input->text().toFloat();
    saveLensState(current_lens_index);
    showLensState(current_lens_index);
}

//          Methods         //
void MainWindow::saveLensState(int index)
{
    LensState prev_state = lenses_states[index];

    float new_x = ui->lensesXInput->text().toFloat();
    float new_focal_length = ui->lensesSettingFocalLenInput->text().toFloat();
    bool new_is_active = ui->lensesSelectCheckBox->isChecked();
    bool new_is_focal_length_set = ui->lensesSettingRBFocalLen->isChecked();
    float new_r1;
    float new_r2;

    if (new_is_focal_length_set && !prev_state.is_focal_length_set) {
        new_r1 = ui->lensesSettingR1Input->text().toFloat();
        new_r2 = ui->lensesSettingR2Input->text().toFloat();
    } else {
        new_r1 = prev_state.r1;
        new_r2 = prev_state.r2;
    }

    LensState new_state = {
        .x = new_x,
        .focal_length = new_focal_length,
        .r1 = new_r1,
        .r2 = new_r2,
        .is_active = new_is_active,
        .is_focal_length_set = new_is_focal_length_set
    };

    lenses_states[index] = new_state;
}

void MainWindow::showLensState(int index)
{
    LensState current_lens_state = lenses_states[index];

    ui->lensesXInput->setText(QString::number(current_lens_state.x));
    ui->lensesSelectCheckBox->setChecked(current_lens_state.is_active);
    if (current_lens_state.is_focal_length_set) {
        ui->lensesSettingRBFocalLen->setChecked(true);
        ui->lensesSettingFocalLenInput->setText(QString::number(current_lens_state.focal_length));
        ui->lensesSettingFocalLenInput->setDisabled(false);
        ui->lensesSettingR1Input->setText("");
        ui->lensesSettingR2Input->setText("");
        ui->lensesSettingR1Input->setDisabled(true);
        ui->lensesSettingR2Input->setDisabled(true);
    } else {
        float focal_len = Lens::calculateFocalLen(current_lens_state.r1, current_lens_state.r2);
        ui->lensesSettingRBRadius->setChecked(true);
        ui->lensesSettingR1Input->setText(QString::number(current_lens_state.r1));
        ui->lensesSettingR2Input->setText(QString::number(current_lens_state.r2));
        ui->lensesSettingFocalLenInput->setText(QString::number(focal_len));
        ui->lensesSettingFocalLenInput->setDisabled(true);
        ui->lensesSettingR1Input->setDisabled(false);
        ui->lensesSettingR2Input->setDisabled(false);
    }
}

void MainWindow::showImageStats(Image image)
{
    ui->imageStatsXOutput->setText(QString::number(image.get_x_coordinate()));
    ui->imageStatsSizeOutput->setText(QString::number(image.get_size()));

    if (image.get_orientation() == ObjectOrientation::up)
        ui->imageStatsOrientationOutput->setText("вверх");
    else if (image.get_orientation() == ObjectOrientation::down)
        ui->imageStatsOrientationOutput->setText("вниз");

    if (image.get_type() == ImageType::real)
        ui->imageStatsTypeOutput->setText("РЕАЛЬНОЕ");
    else if (image.get_type() == ImageType::imaginary)
        ui->imageStatsTypeOutput->setText("МНИМОЕ");
}


