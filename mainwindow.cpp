
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lenses_settings(5)
{
    ui->setupUi(this);

    // initialize lenses select combo box
    for (int i = 1; i <= 5; ++i)
    {
        ui->lensesSelectComboBox->addItem(QString::number(i));
    }
    ui->lensesSelectComboBox->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_menuCalculateButton_clicked()
{
    float object_x = ui->objectXInput->text().toFloat();
    float object_size = ui->objectSizeInput->text().toFloat();
    ObjectOrientation object_orientation;
    if (ui->objectOrientationRBUp->isChecked())
        object_orientation = ObjectOrientation::up;
    else
        object_orientation = ObjectOrientation::down;

    saveLensSettings(ui->lensesSelectComboBox->currentIndex());

    model.set_object(Object(object_x, object_size, object_orientation));
    for (int i = 0; i < 5; ++i)
        model.setLens(i, Lens(lenses_settings[i].x, lenses_settings[i].focal_length, lenses_settings[i].is_active));

    model.calculate();
    Image result_image = model.get_image();

    showImageStats(result_image);
}

void MainWindow::on_lensesSelectComboBox_currentIndexChanged(int index)
{
    saveLensSettings(prev_lens_index);
    showCurrentLensSettings(index);
    prev_lens_index = index;
}

void MainWindow::saveLensSettings(int index)
{
    float new_x = ui->lensesXInput->text().toFloat();
    float new_focal_length = ui->lensesSettingFocalLenInput->text().toFloat();
    bool new_is_active = ui->lensesSelectCheckBox->isChecked();

    LensSettings new_settings = {
        .x = new_x,
        .focal_length = new_focal_length,
        .is_active = new_is_active
    };
    lenses_settings[index] = new_settings;
}

void MainWindow::showCurrentLensSettings(int index)
{
    LensSettings current_lens_settings = lenses_settings[index];

    ui->lensesXInput->setText(QString::number(current_lens_settings.x));
    ui->lensesSettingFocalLenInput->setText(QString::number(current_lens_settings.focal_length));
    ui->lensesSelectCheckBox->setChecked(current_lens_settings.is_active);
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
