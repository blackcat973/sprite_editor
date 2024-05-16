/**
 * @author  Simon Padgen
 * @review  Carly Atwell
 */

#ifndef PIXEL_H
#define PIXEL_H

class Pixel{

public:
    int red;
    int green;
    int blue;
    int alpha;
    Pixel();
    Pixel(int setRed,int setGreen, int setBlue, int setAlpha);
    Pixel operator=(const Pixel& otherPixel);
    ~Pixel();
};

#endif // PIXEL_H
