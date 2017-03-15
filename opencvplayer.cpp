#include "opencvplayer.h"
#include <QDebug>

OpenCVPlayer::OpenCVPlayer(QObject *parent) : QThread(parent)
{
    stop = true;
}

OpenCVPlayer::~OpenCVPlayer() {
    mutex.lock();
    stop = true;
    capture.release();
    waitCondition.wakeOne();
    mutex.unlock();
    wait();
}

bool OpenCVPlayer::loadVideo(std::string fileName) {
    capture.open(fileName);
    if (capture.isOpened()) {
        frameRate = (int)capture.get(CV_CAP_PROP_FPS);
        return true;
    } else {
        return false;
    }
}

bool OpenCVPlayer::loadVideo(int index) {
    capture.open(index);
    if(capture.isOpened()) {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    } else {
        return false;
    }
}

void OpenCVPlayer::Play() {
    if(!isRunning()) {
        if(isStopped()) {
            stop = false;
        }
        start(LowPriority);
        qDebug() << "Player started..(stop:" << isStopped() << ")" << endl;
    }
}

void OpenCVPlayer::run() {
    int delay = 10;
    qDebug() << "OpenCVPlayer::run" << endl;
    while(!stop) {
        if(!capture.read(frame)) {
            stop = true;
            qDebug() << "Cannot read frame from video source!!" << endl;
        } else {
            qDebug() << "Frame(channels:" << frame.channels() << ")" << endl;
            if(frame.channels() == 3) {
                cvtColor(frame, RGBFrame, CV_BGR2RGB);
                image = QImage((const unsigned char*)RGBFrame.data, RGBFrame.cols, RGBFrame.rows, QImage::Format_RGB888);
            } else {
                image = QImage((const uchar *)frame.data, frame.cols, frame.rows, QImage::Format_Indexed8);
            }
            emit processedImage(image);
        }
    }
}

void OpenCVPlayer::Stop() {
    stop = true;
}


bool OpenCVPlayer::isStopped() {
    return this->stop;
}
