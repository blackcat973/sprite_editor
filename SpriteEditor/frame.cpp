/**
 * @author  Simon Padgen
 * @review  SangYoon Cho
 */

#include "frame.h"
#include "pixel.h"

/// @brief Frame constructor accepting a resolution
/// @param res
Frame::Frame(int res){

    resolution = res;
    // initialize each pixel in the frame to white
    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            pixels[i][j] = Pixel();
        }
    }

}

/// @brief Frame destructor
Frame::~Frame(){
    // empty may be ok, we'll see
}

void Frame::changeRes(int newRes)
{
    resolution = newRes;
}

/// @brief method to change the value of a pixel
/// @param x
/// @param y
/// @param newPixel
void Frame::changePixel(int x, int y, Pixel* newPixel){

    pixels[x][y] = *newPixel;
}

/// @brief method to apply a flip over the "y axis" transform to the current frame
void Frame::flipY(){

    // make a copy
    Pixel copy[resolution][resolution];

    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            copy[i][j] = pixels[i][j];
        }
    }

    // do the flip math and transform
    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            pixels[i][j] = copy[resolution - i - 1][j];
        }
    }



}

/// @brief method to apply a flip over the "x axis" transform to the current frame
void Frame::flipX(){

    // make a copy
    Pixel copy[resolution][resolution];

    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            copy[i][j] = pixels[i][j];
        }
    }

    // do the flip math and transform
    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            pixels[i][j] = copy[i][resolution - j - 1];
        }
    }
}

/// @brief method to apply rotate the frame clockwise
void Frame::rotateCW(){

    // make a copy
    Pixel copy[resolution][resolution];

    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            copy[i][j] = pixels[i][j];
        }
    }

    // do the rotate math and transform
    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            pixels[resolution-j-1][i] = copy[i][j];
        }
    }
}

/// @brief method to apply rotate the frame counter-clockwise
void Frame::rotateCCW(){

    // make a copy
    Pixel copy[resolution][resolution];

    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            copy[i][j] = pixels[i][j];
        }
    }

    // do the rotate math and transform
    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){
            pixels[i][j] = copy[resolution-j-1][i];
        }
    }
}

void Frame::setFrameName(QString name){
    frameName = name;
}


