/**
 * This class is for creating and showing preview window of animation of frames.
 *
 * @author      SangYoon Cho
 * @review      Carly Atwell, Simon Padgen
 */

#include "previewwindow.h"
#include "ui_previewwindow.h"

/**
 * @brief PreviewWindow::PreviewWindow: Construct preview window with initial fps value.
 * @param parent
 */
PreviewWindow::PreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWindow){
    ui->setupUi(this);

    count = 0;  // This is for count frames size
    FPS = 1000; // Time delay

    delayTimer.stop();
}

/**
 * @brief PreviewWindow::~PreviewWindow: Destructor
 */
PreviewWindow::~PreviewWindow(){
    delete ui;
}

/**
 * @brief PreviewWindow::getImageListFromModel: Get all frames' image from ModelController
 * @param imglist:  QVector<QImage> that contains all images of frames
 */
void PreviewWindow::getImageListFromModel(QVector<QImage> imglist){
    imageListFromModel = imglist;
}

/**
 * @brief PreviewWindow::showPreviewAnimation: Start animation
 */
void PreviewWindow::showPreviewAnimation(){
    if(!delayTimer.isActive()){
        delayTimer.start(0);    // Start animation

        activeAnimation();
    }
}

/**
 * @brief PreviewWindow::activeAnimation: Recursion to show all images.
 * When it shows the last image, it goes back to the first image and show all images again.
 * The speed of animation is based on FPS value.
 */
void PreviewWindow::activeAnimation(){
    ui->animationFrame->setPixmap(QPixmap::fromImage(imageListFromModel[count].scaled(300, 300)));

    count++;

    if(count == imageListFromModel.size()){
        count = 0;
    }

    delayTimer.singleShot(FPS, this, &PreviewWindow::activeAnimation); // Recursive to show frames one by one
}

/**
 * @brief PreviewWindow::setFramePerSecond: Set FPS value.
 * @param fps:  Integer fps value from MainWindow UI
 */
void PreviewWindow::setFramePerSecond(int fps){
    FPS = 1000 / fps;
}
