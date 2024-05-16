/**
 * This method is for showing the progression of drawing.
 *
 * @author  Carly Atwell
 * @assist  MinGyu Jung: connect and update current color that is selected by user
 * @review  Simon Padgen, SangYoon Cho
 */

#include "drawingpanel.h"

using namespace std;

/**
 * @brief clearImage: resets the image to display
 * @param image: a reference to the image to reset
 * @param width: width of the new blank image
 * @param height: height of the new blank image
 */
static void clearImage(QImage &image, int width, int height){
    image = QImage(width,height,QImage::Format_RGB888);
    image.fill(QColor(Qt::white));
}

/**
 * @brief DrawingPanel::DrawingPanel: constructs DrawingPanel with
 * initial pen color black and blank image
 * @param parent: QWidget parent
 */
DrawingPanel::DrawingPanel(QWidget *parent) : QWidget(parent){
    penColor = QColor(Qt::black);
    clearImage(image, width(), height());
}

/**
 * @brief DrawingPanel::~DrawingPanel
 */
DrawingPanel::~DrawingPanel(){

}

/**
 * @brief DrawingPanel::setResolution: sets the resolution of the image
 * @param res: Resolution in pixels that fit across the width/height of the drawing panel
 * Resolution should be a factor of 512
 */
void DrawingPanel::setResolution(int res){
    resolution = res;
}

/**
 * @brief DrawingPanel::setEnabled: Enables drawing/erasing on the drawing panel
 * @param en: True to enable drawing and false to disable drawing
 */
void DrawingPanel::setEnabled(bool en){
    enabled = en;
}

/**
 * @brief DrawingPanel::setMirrorEnabled: Enables mirrored drawing on the drawing panel
 * @param en: True to enable mirrored drawing and false to disable
 */
void DrawingPanel::setMirrorEnabled(bool en){
    mirrorEnabled = en;
}

/**
 * @brief DrawingPanel::setMirrorEnabled: Enables erasing on the drawing panel
 * @param en: True to enable erasing and false to disable
 */
void DrawingPanel::setEraserEnabled(bool en){
    eraserEnabled = en;
}

/**
 * @brief DrawingPanel::drawPixel: Draws the appropriate amount of pixels based on
 * the resolution and image size
 * @param pt: QPoint point from mouse event
 */
void DrawingPanel::drawPixel(QPoint pt){

    // only if drawing/erasing is enabled
    if(mirrorEnabled){
        // # of actual pixels in the width/height of one sprite pixel
        int pixelSize = (image.width() / resolution) * penSize;

        // get the number of actual pixels to fill in to the left of the mouse point x value
        int pixLeft = pt.x() % pixelSize;
        // get the number of actual pixels to fill in above the mouse point y value
        int pixAbove = pt.y() % pixelSize;

        // fills in the appropraite square of pixels that represents one sprite pixel
        int startX = pt.x() - pixLeft;
        int startY = pt.y() - pixAbove;
        for(int i = 0; i < pixelSize; i++){
            for(int j = 0; j < pixelSize; j++){
                // check for out of bounds drawing
                if(0 <= startX+i && startX+i < 512 && 0 <= startY+i && startY+i < 512){
                    image.setPixelColor(startX+i,startY+j, penColor);
                }
            }
        }

        // send signal to modelcontroller to set appropriate sprite pixel
        int x = startX / (image.width() / resolution);
        int y = startY / (image.width() / resolution);

        // check for out of bounds drawing
        if(0 <= x && x < resolution && 0 <= y && y < resolution){
            for(int i = 0; i < penSize; i++){
                for(int j = 0; j < penSize; j++){
                    emit setPixel(x+i,y+j, penColor);
                }
            }
        }

        // fills in the mirrored pixel
        int startMirrorX = image.width() - startX - pixelSize;
        for(int i = 0; i < pixelSize; i++){
            for(int j = 0; j < pixelSize; j++){
                // check for out of bounds drawing
                if(0 <= startMirrorX+i && startMirrorX+i < 512 && 0 <= startY+i && startY+i < 512){
                    image.setPixelColor(startMirrorX+i,startY+j, penColor);
                }
            }
        }

        // send signal to modelcontroller to set mirrored sprite pixel
        int xMirror = startMirrorX / (image.width() / resolution);
        if(0 <= xMirror && xMirror < resolution && 0 <= y && y < resolution){
            for(int i = 0; i < penSize; i++){
                for(int j = 0; j < penSize; j++){
                    emit setPixel(xMirror+i,y+j, penColor);
                }
            }
        }
    }
    else if(enabled){
        // # of actual pixels in the width/height of one sprite pixel
        int pixelSize = (image.width() / resolution) * penSize;

        // get the number of actual pixels to fill in to the left of the mouse point x value
        int pixLeft = pt.x() % pixelSize;
        // get the number of actual pixels to fill in above the mouse point y value
        int pixAbove = pt.y() % pixelSize;

        // fills in the appropraite square of pixels that represents one sprite pixel
        int startX = pt.x() - pixLeft;
        int startY = pt.y() - pixAbove;
        for(int i = 0; i < pixelSize; i++){
            for(int j = 0; j < pixelSize; j++){
                // check for out of bounds drawing
                if(0 <= startX+i && startX+i < 512 && 0 <= startY+i && startY+i < 512){
                    image.setPixelColor(startX+i,startY+j, penColor);
                }
            }
        }

        // send signal to modelcontroller to set appropriate sprite pixel
        int x = startX / (image.width() / resolution);
        int y = startY / (image.width() / resolution);
        // check for out of bounds drawing
        if(0 <= x && x < resolution && 0 <= y && y < resolution){
            for(int i = 0; i < penSize; i++){
                for(int j = 0; j < penSize; j++){
                    emit setPixel(x+i,y+j, penColor);
                }
            }
        }
    }
    else if(eraserEnabled){
        QColor white = QColor(255, 255, 255);

        // # of actual pixels in the width/height of one sprite pixel
        int pixelSize = (image.width() / resolution) * penSize;

        // get the number of actual pixels to fill in to the left of the mouse point x value
        int pixLeft = pt.x() % pixelSize;
        // get the number of actual pixels to fill in above the mouse point y value
        int pixAbove = pt.y() % pixelSize;

        // fills in the appropraite square of pixels that represents one sprite pixel
        int startX = pt.x() - pixLeft;
        int startY = pt.y() - pixAbove;
        for(int i = 0; i < pixelSize; i++){
            for(int j = 0; j < pixelSize; j++){
                // check for out of bounds drawing
                if(0 <= startX+i && startX+i < 512 && 0 <= startY+i && startY+i < 512){
                    image.setPixelColor(startX+i,startY+j, white);
                }
            }
        }

        // send signal to modelcontroller to set appropriate sprite pixel

        int x = startX / (image.width() / resolution);
        int y = startY / (image.width() / resolution);
        // check for out of bounds drawing
        if(0 <= x && x < resolution && 0 <= y && y < resolution){
            for(int i = 0; i < penSize; i++){
                for(int j = 0; j < penSize; j++){
                    emit setPixel(x+i,y+j, white);
                }
            }
        }
    }
}

/**
 * @brief DrawingPanel::drawFromFrameArray: sets the pixels of the image from Frame data
 * Used for loading a frame to the UI and displaying transformations
 * @param frame: Frame withe array of pixel values to be drawn
 */
void DrawingPanel::drawFromFrameArray(Frame* frame){
    // set DrawingPanel resolution to Frame resolution
    resolution = frame->resolution;
    int pixelSize = image.width() / resolution;

    // first two for loops iterate through the frame array of sprite pixels
    for(int x = 0; x < resolution; x++){
        for(int y = 0; y < resolution; y++){

            Pixel pixel;
            pixel = frame->pixels[x][y];
            QColor pixelColor = QColor(pixel.red, pixel.green, pixel.blue, pixel.alpha);

            // iterate through the real pixels of this one sprite pixel
            for(int i = 0; i < pixelSize; i++){
                for(int j = 0; j < pixelSize; j++){
                    image.setPixelColor((pixelSize*x) + i, (pixelSize*y) + j, pixelColor);
                }
            }
        }
    }
}

/**
 * @brief DrawingPanel::mousePressEvent: calls the drawPixel method and repaint to trigger paintEvent
 * @param event
 */
void DrawingPanel::mousePressEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        drawPixel(event->pos());
        repaint();
    }
    emit sendCurrentImage(image);
}

/**
 * @brief DrawingPanel::mouseMoveEvent: calls the drawPixel method and repaint to trigger paintEvent
 * This makes drawing while dragging the mouse work
 * @param event
 */
void DrawingPanel::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        drawPixel(event->pos());
        repaint();
    }
    emit sendCurrentImage(image);
}

/**
 * @brief DrawingPanel::resizeEvent: Resets the image upon resize event
 * @param event
 */
void DrawingPanel::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);
    QImage newImage;
    clearImage(newImage, 512, 512);

    QPainter p(&newImage);
    p.drawImage(0,0,image);

    image = newImage;

    update();
}

/**
 * @brief DrawingPanel::drawColor: returns the current penColor
 * @return
 */
QColor DrawingPanel::drawColor(){
    return penColor;
}

/**
 * @brief DrawingPanel::setDrawColor: sets the current penColor
 * @param color: QColor color to set the penColor to
 */
void DrawingPanel::setDrawColor(QColor color){
    penColor = color;
}

/**
 * @brief DrawingPanel::clear: clears the image and calls update to update the display
 */
void DrawingPanel::clear(){
    clearImage(image, 512, 512);
    update();
}

/**
 * @brief DrawingPanel::paintEvent: Upon a paint event, makes a QPainter to draw the image
 * on this DrawingPanel widget
 * @param event
 */
void DrawingPanel::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    QPixmap pixmap = QPixmap::fromImage(image);
    painter.drawPixmap(0,0,pixmap);
}

/**
 * @brief DrawingPanel::updateDrawingPanelSlot: Slot for when the underlying frame data structure is
 * changed so we need to redraw the drawing panel display based on the changed/new frame
 * @param frame: frame to display
 */
void DrawingPanel::updateDrawingPanelSlot(Frame* frame){
    // clear current image
    QImage newImage;
    clearImage(newImage, 512, 512);

    // update image
    drawFromFrameArray(frame);
    // trigger paint event
    repaint();
    emit sendCurrentImage(image);
}

/**
 * @brief DrawingPanel::changePenSizeSlot: slot for changing the drawing pen size
 * @param size: how many sprite pixels the pen should fill in
 */
void DrawingPanel::changePenSizeSlot(int size){
    penSize = size;
}
