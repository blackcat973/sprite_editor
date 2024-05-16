/**
 * This class controls all 'Model' datas and send data to proper class.
 * It stores    framesList for control all frames,
 *              colorList for control pen color and choosing and drawing in the drawing panel,
 *              imageList for control actual image on the drawing panel to send to the scroll area and preview animation,
 *              currColor for control current selected color,
 *              currFrame for control current selected frame,
 *              currIndex for control current frame's index in framesList
 *              clearFrames for clear data for load method.            
 * @author      SangYoon Cho, Mingyu Jung, Carly Atwell
 * @assist      Simon Padgen
 * @review      LeiLei Shen
 */

#include "modelcontroller.h"

/**
 * @brief ModelController::ModelController: Construct ModelControllor with initial frame.
 *        It is basically setting what the program should to have in the initialization.
 * @param parent: QObject *parent
 */
ModelController::ModelController(QObject *parent) : QObject{parent}{
    framesList.push_back(new Frame(128));
    currIndex = 0;
    currFrame = framesList.first();
    framesList.first()->frameName.append("Frame0");

    // Make a new white image for new frame
    QImage image = QImage(500,500,QImage::Format_RGB888);
    image.fill(QColor(Qt::white));
    imageList.push_back(image);

    for(int i=0; i<10; i++){
        QColor color;
        colorList.push_back(color);
    }
}

/**
 * @brief ModelController::~ModelController: Destructor
 */
ModelController::~ModelController(){
    clearFrames();
}

/**
 * @brief ModelController::clearFrames: Clear and delete all datas in the ModelController
 * for loading or for destructor.
 * And then send signals(sendClear()) to the MainWindow to clear frameComboBox.
 */
void ModelController::clearFrames(){
    // delete frame pointer variable
    for(int i=0; i<framesList.size(); i++){
        delete framesList[i];
    }

    framesList.clear();
    imageList.clear();

    currIndex = -1;
    currFrame = nullptr;
    emit sendClear();
}

/**
 * @brief ModelController::addFrame: Invoked when user clicks '+Frame' button.
 * Create one new frame, and add it into the framesList.
 * It automatically set current frame as the new frame, and then send two signals.
 *                              - addFinish(-> MainWindow): Change UI information as a new frame
 *                              - updateDrawingPanel(-> DrawingPanel): Update new image on drawing panel as new frame.
 */
void ModelController::addFrame(){
    if(framesList.size()<101)
    {
        currIndex += 1;

        QImage image = QImage(500,500,QImage::Format_RGB888);
        image.fill(QColor(Qt::white));
        imageList.push_back(image);

        framesList.append(new Frame(128));
        currFrame = framesList.last();

        QString fName = "Frame" + QString::number(currIndex);
        framesList.last()->frameName.append(fName);

        emit addFinish(currIndex, currFrame);
        emit updateDrawingPanel(currFrame);
    }
}

/**
 * @brief ModelController::deleteFrame: Invoked when user clicks '-Frame' button.
 * Remove current frame(selected frame by user) from framesList and imageList.
 * After it removes the current frame, it send signals
 *                              - deleteFinish(-> MainWindow): Change UI information as next index frame.
 */
void ModelController::deleteFrame(){
    if(framesList.size()>1)
    {
        framesList.removeAt(currIndex);
        imageList.removeAt(currIndex);

        if(currIndex > framesList.size())
            currIndex -= 1;

        emit deleteFinish(currIndex);
    }
}

/**
 * @brief ModelController::getCurrFrameIndex: Set current frame.
 * It sends two signals.        - sendResolutionValue(->MainWindow): Change UI information as current frame
 *                              - updateDrawingPanel(->DrawingPanel): Update new image on drawing panel as the current frame.
 * @param fra: int value to get index of frame
 */
void ModelController::getCurrFrameIndex(int fra){
    currIndex = fra;
    currFrame = framesList.at(currIndex);

    emit sendResolutionValue(currFrame);
    emit updateDrawingPanel(currFrame);
}

/**
 * @brief ModelController::setResolution: Set resolution of current frame
 * @param res: integer resolution value
 */
void ModelController::setResolution(int res){
    currFrame->changeRes(res);

    emit updateDrawingPanel(currFrame);
}

/**
 * @brief ModelController::setFrameName: Set name of frame
 * @param name: QString to set name of frame
 */
void ModelController::setFrameName(QString name){
    currFrame->setFrameName(name);
}


/**
 * @brief ModelController::getCurrColor: getting current color.
 * It sends one signal.         - sendColor(->DrawingPanel): Change color
 * @param idx: which button is it.
 */
void ModelController::getCurrColor(int idx){
     currColor = colorList[idx];

     emit sendColor(currColor);
}

/**
 * @brief ModelController::setCurrColor: setting up current color
 *  * It sends one signal.         - sendColor(->DrawingPanel): Change color
 * @param color
 * @param idx: which button is it
 */
void ModelController::setCurrColor(QColor color, int idx){
    colorList[idx] = color;
    currColor = colorList[idx];

    emit sendColor(currColor);
}

/**
 * @brief ModelController::setPixelSlot: Slot that recieves signal setPixel from drawingPanel
 * when the user draws a pixel on the UI
 * @param x: Frame pixel x coordinate
 * @param y: Frame pixel y coordinate
 */
void ModelController::setPixelSlot(int x, int y, QColor col){
    Pixel rgbPixelVal(col.red(), col.green(), col.blue(), col.alpha());

    currFrame->changePixel(x, y, &rgbPixelVal);
}

/**
 * @brief ModelController::save the height, width, numberOfFrames, and all frames that is included
 * in the frameList as JSON format
 * @param fileName: file name that user put
 * @param filePath: file path that user put
 */
void ModelController::save(QString fileName, QString filePath) {
    //  JSON object that is included all datas that needs to be stored.
    QJsonObject saveObject;

    //  insert height which is fixed as 128
    saveObject.insert("height", 128);
    //  insert width which is fixed as 128
    saveObject.insert("width", 128);
    //  insert numberOfFrames which is frameList length.
    saveObject.insert("numberOfFrames", framesList.length());
    //  JSON object that is containing all frames.
    QJsonObject frameObject;
    //  go thorugh all frames in framesList
    foreach(const Frame* frame, framesList){
        //  JSON array that is containg pixels
        QJsonArray pixelArray;

        for(int i=0; i< 128; i++){
            for(int j=0; j< 128; j++){
                //  JSON array that is containg pixel colors
                QJsonArray onePixel;

                onePixel.push_back(frame->pixels[i][j].red);
                onePixel.push_back(frame->pixels[i][j].green);
                onePixel.push_back(frame->pixels[i][j].blue);
                onePixel.push_back(frame->pixels[i][j].alpha);

                pixelArray.push_back(QJsonValue(onePixel));
            }
        }
        //  push back resolution at the end of the pixelArray
        pixelArray.push_back(frame->resolution);

        //  insert pixelArray as frameName
        frameObject.insert(frame->frameName, pixelArray);
        //  insert frameObject to frames
        saveObject.insert("frames", frameObject);
    }

    //  create the file to save
    QFile file(filePath + "/" + fileName);
    //  convert to document
    QJsonDocument doc(saveObject);

    if (file.open(QIODevice::WriteOnly)) {
        qDebug() << "saved";
    }
    file.write(doc.toJson());
    file.close();
}

/**
 * @brief ModelController::load: load .ssp file and applied every datas
 * into curent running program.
 * @param fileName: full path by user selected
 */
void ModelController::load(QString fileName){

    //  create the file object by passed path
    QFile file(fileName);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );

    if(document.isObject()){
        //  JSON object for opening document
        QJsonObject jsonObj = document.object();

        int width = jsonObj.value("width").toInt();
        int height = jsonObj.value("height").toInt();
        int numberOfFrames = jsonObj.value("numberOfFrames").toInt();

        QJsonValue frames = jsonObj.value("frames");
        QJsonObject framesObject = frames.toObject();
        //clear all frames to load file.
        clearFrames();

        foreach(const QString& key, framesObject.keys()) {

            QJsonValue frameValue = framesObject.value(key);
            QJsonArray pixelArray = frameValue.toArray();

            //create the new Frame to insert.
            Frame* current = new Frame(width);
            //set up frame name
            current->frameName = key;

            //loop for setting up pixels
            int pixelIndex = 0;
            for(int j=0; j<height; j++){
                for(int k=0; k<width; k++){
                    //insert all pixels that is loaded to current pixels
                    current->pixels[j][k].red = pixelArray.at(pixelIndex)[0].toInt();
                    current->pixels[j][k].green = pixelArray.at(pixelIndex)[1].toInt();
                    current->pixels[j][k].blue = pixelArray.at(pixelIndex)[2].toInt();
                    current->pixels[j][k].alpha = pixelArray.at(pixelIndex)[3].toInt();
                    pixelIndex++;
                }
            }
            //  change resolution as loaded resolution
            current->resolution = pixelArray.last().toInt();
            //  insert frame to the framesList
            framesList.push_back(current);
            //  change currentFrame to the lastest frame.
            currFrame = framesList.last();

            currIndex += 1;

            emit addFinish(currIndex, currFrame);
            emit updateDrawingPanel(currFrame);
        }
    }
    qDebug() << "load success";
}

void ModelController::xFlipSlot(){
    currFrame->flipX();

    emit updateDrawingPanel(currFrame);
}

void ModelController::yFlipSlot(){
    currFrame->flipY();

    emit updateDrawingPanel(currFrame);
}

void ModelController::rotateCWSlot(){
    currFrame->rotateCW();

    emit updateDrawingPanel(currFrame);
}

void ModelController::rotateCCWSlot(){
    currFrame->rotateCCW();

    emit updateDrawingPanel(currFrame);
}

/**
 * @brief ModelController::getFramesImageFromDrawingPanel: Add or replace images of frames into imageList.
 * It takes images of frames on the drawing panel immediately, and send one signal
 *                              - sendFrameImageList(-> PreviewWindow, -> MainWindow): Send all images of frames.
 * @param img: Image of current frame from DrawingPanel
 */
void ModelController::getFramesImageFromDrawingPanel(QImage img){
    if (imageList.size() != framesList.size()){
        imageList.push_back(img);
    }
    else{
        imageList.replace(currIndex, img);
    }

    emit sendFrameImageList(imageList);
}
