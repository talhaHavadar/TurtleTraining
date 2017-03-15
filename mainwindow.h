#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencvplayer.h"
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updatePlayerUI(QImage image);
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    OpenCVPlayer *player;
};

#endif // MAINWINDOW_H
