#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencvplayer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSet>
#include <opencv2/opencv.hpp>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void handleKeyboardInput();
private slots:
    void updatePlayerUI(QImage image);
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    OpenCVPlayer *player;
    QSet<Qt::Key> pressedKeys;
    int timerId;
    Mat directions;
    int getPressedKeyMask();
};

#endif // MAINWINDOW_H
