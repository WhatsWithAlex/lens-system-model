
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>
#include "model.h"
#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_menuCalculateButton_clicked();
    void on_lensesSelectComboBox_currentIndexChanged(int index);
    void on_lensesSettingRBFocalLen_toggled(bool checked);
    void on_lensesSettingR1Input_editingFinished();
    void on_lensesSettingR2Input_editingFinished();
    void on_menuSaveAsButton_clicked();
    void on_menuSaveButton_clicked();
    void on_menuOpenButton_clicked();

private:
    Ui::MainWindow *ui;
    LensSystemModel model;
    QString save_file_path = "";
    int prev_lens_index = 0;
    QList<LensState> lenses_states;
    QGraphicsScene *scene;

    void saveLensState(int index);
    void showLensState(int index);
    void updateModelParams();
    void showImageStats(Image image);
    void saveSettingsToFile();
    void openSettingsFromFile();
};

#endif // MAINWINDOW_H
