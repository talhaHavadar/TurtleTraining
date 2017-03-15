#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    player = new OpenCVPlayer();
    QObject::connect(player, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::updatePlayerUI(QImage image) {
    qDebug() << "MainWindow::updatePlayerUI" << endl;
    if (!image.isNull()) {
        qDebug() << "Update UI " << image.size().width() << " " << image.size().height();
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(image).scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    pressedKeys += (Qt::Key)event->key();
    this->handleKeyboardInput();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    pressedKeys -= (Qt::Key)event->key();
    this->handleKeyboardInput();
}

void MainWindow::getPressedKeyMask() {
    /**
      * 1000 => UP
      * 0111 => DOWN
      * 0010 => LEFT
      * 0001 => RIGHT
     **/


}

void MainWindow::handleKeyboardInput() {
    if (pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A)) {
        qDebug() << "Pressed W and A" << endl;
    } else if (pressedKeys.contains(Qt::Key_W)) {
        qDebug() << "Pressed W" << endl;
    }
}

void MainWindow::on_pushButton_clicked() {
    if(player->isStopped()) {

        if(!player->loadVideo(0)) {
            QMessageBox mBox;
            mBox.setText("Video source cannot be opened!!");
            mBox.exec();
        } else {
            player->Play();
            ui->pushButton->setText(tr("Stop Stream"));
            qDebug() << "Play function called.." << endl;
        }
    } else {
        player->Stop();
        ui->pushButton->setText(tr("Start Stream"));
    }
}
