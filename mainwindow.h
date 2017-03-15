#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencvplayer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSet>

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
    void handleKeyboardInput();
private slots:
    void updatePlayerUI(QImage image);
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    OpenCVPlayer *player;
    QSet<Qt::Key> pressedKeys;
    int getPressedKeyMask();
};

#endif // MAINWINDOW_H
