
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    LensSystemModel model;
    int prev_lens_index = 0;
    QList<LensSettings> lenses_settings;

    void saveLensSettings(int index);
    void showCurrentLensSettings(int index);
    void updateModelParams();
    void showImageStats(Image image);
};

#endif // MAINWINDOW_H
