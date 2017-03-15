#ifndef OPENCVPLAYER_H
#define OPENCVPLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <time.h>

using namespace cv;

class OpenCVPlayer : public QThread
{
    Q_OBJECT
private:
    bool stop;
    QMutex mutex;
    QWaitCondition waitCondition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    Mat RGBFrame;
    QImage image;
signals:
    void processedImage(const QImage &image);
protected:
    void run();
public:
    OpenCVPlayer(QObject *parent = 0);
    ~OpenCVPlayer();
    bool loadVideo(std::string fileName);
    bool loadVideo(int index);
    void Play();
    void Stop();
    bool isStopped();
};

#endif // OPENCVPLAYER_H
