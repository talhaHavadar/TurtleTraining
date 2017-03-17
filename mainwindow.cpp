#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    player = new OpenCVPlayer();
    QObject::connect(player, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));

    directions = Mat::zeros(5,5, CV_32F);
    for(int i = 0; i < directions.rows; i++) {
        directions.at<float>(i, i) = 1;
        // print out directions matrix
        std::ostringstream ss;
        for(int j = 0; j < directions.cols; j++) {
            if(j == 0)
                ss << "[";
            if(j == directions.cols - 1)
                ss << directions.at<float>(i, j) << "]" << endl;
            else
                ss << directions.at<float>(i, j) << ",";
        }
        qDebug() << ss.str().c_str() << endl;
    }

    Mat t = Mat::zeros(1,5, CV_32F);
    directions.push_back(t);
    qDebug() << "Mat test: " << directions.rows << endl;
    timerId = startTimer(50);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::updatePlayerUI(QImage image) {
    if (!image.isNull()) {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(image).scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    pressedKeys += (Qt::Key)event->key();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    pressedKeys -= (Qt::Key)event->key();
}

void MainWindow::timerEvent(QTimerEvent *event) {
    if(pressedKeys.size() > 0) {
        handleKeyboardInput();
    } else {
        ui->lblCurrentKeys->setText("- || -----");
    }
}

void MainWindow::handleKeyboardInput() {
    Mat frame = player->Read();
    qDebug() << "Last Frame: " << frame.cols << "x" << frame.rows << endl;


    if (pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A) && pressedKeys.contains(Qt::Key_K)) {
        qDebug() << "Pressed W and A (Full Left)" << endl;
        ui->lblCurrentKeys->setText("W + A + K || Full Left");
    } else if (pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_L)) {
        qDebug() << "Pressed W and D (Full Right)" << endl;
        ui->lblCurrentKeys->setText("W + A + L || Full Right");
    } else if (pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A)) {
        qDebug() << "Pressed W and A" << endl;
        ui->lblCurrentKeys->setText("W + A || Left");
    } else if (pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_D)) {
        qDebug() << "Pressed W and D" << endl;
        ui->lblCurrentKeys->setText("W + D || Right");
    } else if(pressedKeys.contains(Qt::Key_A)) {
        qDebug() << "Pressed A" << endl;
    } else if(pressedKeys.contains(Qt::Key_D)) {
        qDebug() << "Pressed D" << endl;
    } else if (pressedKeys.contains(Qt::Key_W)) {
        qDebug() << "Pressed W" << endl;
        ui->lblCurrentKeys->setText("W || Forward");
    }
}

void MainWindow::on_pushButton_clicked() {
    if(player->isStopped()) {

        if(!player->loadVideo("http://217.197.157.7:7070/axis-cgi/mjpg/video.cgi?resolution=320x240")) {
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
