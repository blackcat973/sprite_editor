#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QColor>
#include <QImage>
#include <fstream>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QByteArray>
#include <iostream>
#include <QFileDialog>
#include "frame.h"

class ModelController : public QObject{
    Q_OBJECT
private:
    QVector<Frame*> framesList;
    QVector<QColor> colorList;
    QVector<QImage> imageList;
    QColor currColor;
    Frame* currFrame;
    int currIndex;
    void clearFrames();


public slots:
    void addFrame();
    void deleteFrame();
    void setResolution(int res);
    void getCurrFrameIndex(int fra);
    void setFrameName(QString name);
    void getCurrColor(int idx);
    void setCurrColor(QColor color, int idx);
    void setPixelSlot(int x, int y, QColor col);
    void save(QString fileName, QString filePath);
    void load(QString fileName);
    void xFlipSlot();
    void yFlipSlot();
    void rotateCWSlot();
    void rotateCCWSlot();
    void getFramesImageFromDrawingPanel(QImage img);

signals:
    void sendClear();
    void sendColor(QColor color);
    void updateDrawingPanel(Frame* frame);
    void addFinish(int currIndex, Frame* fra);
    void deleteFinish(int currIndex);
    void sendResolutionValue(Frame* fra);
    void sendFrameImageList(QVector<QImage> imgList);

public:
    explicit ModelController(QObject *parent = nullptr);

    ~ModelController();
signals:

};

#endif // MODELCONTROLLER_H
