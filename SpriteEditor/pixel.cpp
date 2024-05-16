/**
 * @author Simon Padgen
 * @review SangYoon Cho
 */

#include "pixel.h"

Pixel::Pixel(){
    red = 255;
    green = 255;
    blue = 255;
    alpha = 1;
}

///
/// \brief Pixel::Pixel: Pixel constructor with inputs for each value
/// \param setRed
/// \param setGreen
/// \param setBlue
/// \param setAlpha
///
Pixel::Pixel(int setRed,int setGreen, int setBlue, int setAlpha){
    red = setRed;
    green = setGreen;
    blue = setBlue;
    alpha = setAlpha;
}

/// @brief Equals operators for Pixel
/// @param otherPixel 
/// @return 
Pixel Pixel::operator=(const Pixel& otherPixel){
    red = otherPixel.red;
    green = otherPixel.green;
    blue = otherPixel.blue;
    alpha = otherPixel.alpha;
}

/// @brief Pixel destructor, nothing extra is needed
Pixel::~Pixel(){
}
