/**
 * @author  Simon Padgen
 * @review  SangYoon Cho
 */

#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include "pixel.h"

class Frame{

public:
    Frame(int res);
    ~Frame();
    void changePixel(int x, int y, Pixel *newPixel);
    void changeRes(int newRes);
    void flipY();
    void flipX();
    void rotateCW();
    void rotateCCW();
    void setFrameName(QString name);
    Pixel pixels[128][128];
    int resolution;
    QString frameName;

private:
};

#endif // FRAME_H


