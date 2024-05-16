/**
 * This program is for A6,A7 assignment to create sprite editor.
 *
 * @team member: Carly Atwell
 *               Simon Padgen
 *               MinGyu Jung
 *               SangYoon Cho
 *               Leilei shen
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickevent.h"

#include <QSignalMapper>

MainWindow::MainWindow(ModelController& model, ColorPalette& color, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scrollWidget = new QWidget();
    hlayout = new QHBoxLayout();
    scrollWidget->setLayout(hlayout);

    // set button icons
    QIcon pencilIcon = QIcon(":/Icons/pencil.png");
    ui->drawToolButton->setIcon(pencilIcon);
    QIcon mirrorIcon = QIcon(":/Icons/mirror.png");
    ui->mirrorDrawToolButton->setIcon(mirrorIcon);
    QIcon eraserIcon = QIcon(":/Icons/eraser.png");
    ui->eraseToolButton->setIcon(eraserIcon);
    QIcon rotateCWIcon = QIcon(":/Icons/rotateCW.png");
    ui->rotateCWToolButton->setIcon(rotateCWIcon);
    QIcon rotateCCWIcon = QIcon(":/Icons/rotateCCW.png");
    ui->rotateCCWToolButton->setIcon(rotateCCWIcon);
    QIcon flipXIcon = QIcon(":/Icons/flipX.png");
    ui->xFlipToolButton->setIcon(flipXIcon);
    QIcon flipYIcon = QIcon(":/Icons/flipY.png");
    ui->yFlipToolButton->setIcon(flipYIcon);

    ui->frameComboBox->addItem("Frame" + QString::number(0));

    //=======Set the resolution here=======
    ui->resolutionComboBox->addItem("128");
    ui->resolutionComboBox->addItem("64");
    ui->resolutionComboBox->addItem("32");
    ui->resolutionComboBox->addItem("16");
    //=====================================

    //=======Set the pen size here=======
    ui->penSizeComboBox->addItem("1");
    ui->penSizeComboBox->addItem("2");
    ui->penSizeComboBox->addItem("4");
    ui->penSizeComboBox->addItem("8");
    //=====================================

    ui->animationFps->setText(QString::number(1));
    ui->frameNameEditbox->setText("Frame" + QString::number(0));
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    //===========================================

    //create the button and set up.
    buttonTest0 = new ClickEvent();
    buttonList.push_back(buttonTest0);

    buttonTest1 = new ClickEvent();
    buttonList.push_back(buttonTest1);

    buttonTest2 = new ClickEvent();
    buttonList.push_back(buttonTest2);

    buttonTest3 = new ClickEvent();
    buttonList.push_back(buttonTest3);

    buttonTest4 = new ClickEvent();
    buttonList.push_back(buttonTest4);

    buttonTest5 = new ClickEvent();
    buttonList.push_back(buttonTest5);

    buttonTest6 = new ClickEvent();
    buttonList.push_back(buttonTest6);

    buttonTest7 = new ClickEvent();
    buttonList.push_back(buttonTest7);

    buttonTest8 = new ClickEvent();
    buttonList.push_back(buttonTest8);

    //adding button to the grid.
    ui->colorSelection1->addWidget(buttonTest0);
    buttonTest0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection2->addWidget(buttonTest1);
    buttonTest1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection3->addWidget(buttonTest2);
    buttonTest2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection4->addWidget(buttonTest3);
    buttonTest3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection5->addWidget(buttonTest4);
    buttonTest4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection6->addWidget(buttonTest5);
    buttonTest5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection7->addWidget(buttonTest6);
    buttonTest6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection8->addWidget(buttonTest7);
    buttonTest7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->colorSelection9->addWidget(buttonTest8);
    buttonTest8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //=====================CONNECT=====================
    // From UI

    connect(buttonTest0,  &ClickEvent::rightClicked, this, [this]{onRightClicked(0);});
    connect(buttonTest0,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(0); });

    connect(buttonTest1,  &ClickEvent::rightClicked, this, [this]{onRightClicked(1);});
    connect(buttonTest1,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(1); });

    connect(buttonTest2,  &ClickEvent::rightClicked, this, [this]{onRightClicked(2);});
    connect(buttonTest2,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(2); });

    connect(buttonTest3,  &ClickEvent::rightClicked, this, [this]{onRightClicked(3);});
    connect(buttonTest3,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(3); });

    connect(buttonTest4,  &ClickEvent::rightClicked, this, [this]{onRightClicked(4);});
    connect(buttonTest4,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(4); });

    connect(buttonTest5,  &ClickEvent::rightClicked, this, [this]{onRightClicked(5);});
    connect(buttonTest5,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(5); });

    connect(buttonTest6,  &ClickEvent::rightClicked, this, [this]{onRightClicked(6);});
    connect(buttonTest6,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(6); });

    connect(buttonTest7,  &ClickEvent::rightClicked, this, [this]{onRightClicked(7);});
    connect(buttonTest7,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(7); });

    connect(buttonTest8,  &ClickEvent::rightClicked, this, [this]{onRightClicked(8);});
    connect(buttonTest8,  &ClickEvent::leftClicked, this, [this]{ onLeftClicked(8); });

    connect(ui->addFrameButton,
                &QPushButton::clicked,
                &model,
                &ModelController::addFrame);
    connect(ui->deleteFrameButton,
                &QPushButton::clicked,
                &model,
                &ModelController::deleteFrame);
    connect(ui->previewButton,
                &QPushButton::clicked,
                this,
                &MainWindow::openPreviewWindow);
    connect(ui->frameComboBox,
                &QComboBox::currentIndexChanged,
                this,
                &MainWindow::getCurrFrame);
    connect(ui->frameNameEditbox,
                &QLineEdit::returnPressed,
                this,
                &MainWindow::getFrameName);
    connect(ui->previewButton,
                &QPushButton::clicked,
                &prevWindow,
                &PreviewWindow::showPreviewAnimation);
    connect(ui->resolutionComboBox,
                &QComboBox::currentIndexChanged,
                this,
                &MainWindow::getResolution);
    connect(ui->animationFps,
                &QLineEdit::textChanged,
                this,
                &MainWindow::getFPSValue);

    // From Color
    connect(&color,
            &ColorPalette::backgroundColor,
            this,
            &MainWindow::backgroundColor);
    // From Model Part
    connect(&model,
            &ModelController::sendColor,
            ui->drawingPanel,
            &DrawingPanel::setDrawColor);

    connect(&model,
            &ModelController::addFinish,
            this,
            &MainWindow::takeAddIndexNum);
    connect(&model,
            &ModelController::deleteFinish,
            this,
            &MainWindow::takeDeleteIndexNum);
    connect(&model,
            &ModelController::sendResolutionValue,
            this,
            &MainWindow::takeResolutionValue);
    connect(&model,
            &ModelController::sendClear,
            this,
            &MainWindow::clearOptions);
    connect(&model,
            &ModelController::sendFrameImageList,
            &prevWindow,
            &PreviewWindow::getImageListFromModel);
    connect(&model,
            &ModelController::sendFrameImageList,
            this,
            &MainWindow::takeImageListFromModel);

    //From MainWindow
    connect(this,
            &MainWindow::colorSelected,
            &model,
            &ModelController::getCurrColor);
    connect(this,
            &MainWindow::getColor,
            &color,
            &ColorPalette::colorDialog);
    connect(this,
            &MainWindow::colorUpdate,
            &model,
            &ModelController::setCurrColor);
    connect(this,
            &MainWindow::sendGetCurrFrameIndex,
            &model,
            &ModelController::getCurrFrameIndex);
    connect(this,
            &MainWindow::sendSetResolution,
            &model,
            &ModelController::setResolution);
    connect(this,
            &MainWindow::sendSetFrameName,
            &model,
            &ModelController::setFrameName);
    connect(this,
            &MainWindow::sendFPSValue,
            &prevWindow,
            &PreviewWindow::setFramePerSecond);

    //#############Drawing Part#############
    connect(ui->drawToolButton,
            &QToolButton::clicked,
            this,
            &MainWindow::drawToolButtonClickedSlot);
    connect(ui->eraseToolButton,
            &QToolButton::clicked,
            this,
            &MainWindow::eraseToolButtonClickedSlot);
    connect(ui->mirrorDrawToolButton,
            &QToolButton::clicked,
            this,
            &MainWindow::mirrorDrawToolButtonClickedSlot);
    connect(ui->drawingPanel,
            &DrawingPanel::setPixel,
            &model,
            &ModelController::setPixelSlot);
    connect(ui->penSizeComboBox,
                &QComboBox::currentIndexChanged,
                this,
                &MainWindow::getPenSize);
    connect(this,
            &MainWindow::sendPenSize,
            ui->drawingPanel,
            &DrawingPanel::changePenSizeSlot);
    connect(ui->xFlipToolButton,
            &QToolButton::clicked,
            &model,
            &ModelController::xFlipSlot);
    connect(ui->yFlipToolButton,
            &QToolButton::clicked,
            &model,
            &ModelController::yFlipSlot);
    connect(ui->rotateCWToolButton,
            &QToolButton::clicked,
            &model,
            &ModelController::rotateCWSlot);
    connect(ui->rotateCCWToolButton,
            &QToolButton::clicked,
            &model,
            &ModelController::rotateCCWSlot);
    connect(&model,
            &ModelController::updateDrawingPanel,
            ui->drawingPanel,
            &DrawingPanel::updateDrawingPanelSlot);
    connect(ui->drawingPanel,
            &DrawingPanel::sendCurrentImage,
            &model,
            &ModelController::getFramesImageFromDrawingPanel);

    //=================SAVE AND LOAD=====================
    connect(this,
            &MainWindow::callLoad,
            &model,
            &ModelController::load);
    connect(this,
            &MainWindow::callSave,
            &model,
            &ModelController::save);
}

MainWindow::~MainWindow(){
    delete ui;
}

/**
 * @brief MainWindow::drawToolButtonClickedSlot: Slot for when the draw pencil button in the UI is clicked
 * Sets the drawingPanel anble to true so user may begin drawing
 */
void MainWindow::drawToolButtonClickedSlot(){
    ui->drawingPanel->setMirrorEnabled(false);
    ui->drawingPanel->setEraserEnabled(false);
    ui->drawingPanel->setEnabled(true);
}

void MainWindow::mirrorDrawToolButtonClickedSlot(){
    ui->drawingPanel->setMirrorEnabled(true);
    ui->drawingPanel->setEraserEnabled(false);
    ui->drawingPanel->setEnabled(false);
}

/**
 * @brief MainWindow::eraseToolButtonClickedSlot: Slot for when the eraser  button in the UI is clicked
 * Sets the drawingPanel enable to true so user may begin erasing
 * Sets the penColor to white because erasing is just drawing with a white pen
 */
void MainWindow::eraseToolButtonClickedSlot(){
    ui->drawingPanel->setMirrorEnabled(false);
    ui->drawingPanel->setEnabled(false);
    ui->drawingPanel->setEraserEnabled(true);
}

void MainWindow::onLeftClicked(int idx){
    emit colorSelected(idx);
}

void MainWindow::onRightClicked(int buttonNum){
    emit getColor(buttonNum);
}

void MainWindow::backgroundColor(QColor color, int buttonNum){

    QString qss = QString("background-color: %1").arg(color.name());

    buttonList[buttonNum]->setStyleSheet(qss);

    emit colorUpdate(color, buttonNum);
}

/**
 * @brief MainWindow::takeAddIndexNum: Take signal from ModelController and apply it to the UI.
 * Add index in frameComboBox and frameNameEditbox as frame name.
 * @param currIndex:    Integer to get an index of current frame
 * @param fra:          Frame object that is a current frame
 */
void MainWindow::takeAddIndexNum(int currIndex, Frame* fra){
    if(fra->frameName.isNull()){ // if frame name isn't initialized
        ui->frameComboBox->addItem("Frame" + QString::number(currIndex));
    }else{
        ui->frameComboBox->addItem(fra->frameName);
    }

    ui->frameComboBox->setCurrentIndex(currIndex);
    ui->frameNameEditbox->setText(ui->frameComboBox->currentText());
}

/**
 * @brief MainWindow::takeDeleteIndexNum: Take signal from ModelController and apply it to the UI.
 * Remove index in frameComboBox.
 * @param currIndex:    Integer to get an index of current frame
 * @param fra:          Frame object that is a current frame
 */
void MainWindow::takeDeleteIndexNum(int currIndex){
    ui->frameComboBox->removeItem(currIndex);
}

/**
 * @brief MainWindow::getCurrFrame: Get an index of current frame of frameComboBox.
 * It is invoked when frameComboBox' index is changed.
 * It sends one signal.         - sendGetCurrFrameIndex(->ModelController): Send current frame index
 */
void MainWindow::getCurrFrame(){
    if(ui->frameComboBox->count() != 0){
        ui->frameNameEditbox->setText(ui->frameComboBox->currentText());

        emit sendGetCurrFrameIndex(ui->frameComboBox->currentIndex());
    }
}

/**
 * @brief MainWindow::getFrameName: Get frame name from frameNameEditbox
 * It sends one signal.         - sendSetFrameName(->ModelController): Send current frame name
 */
void MainWindow::getFrameName(){
    QString frameName = ui->frameNameEditbox->text();

    ui->frameComboBox->setItemText(ui->frameComboBox->currentIndex(), frameName);

    emit sendSetFrameName(frameName);
}

/**
 * @brief MainWindow::getResolution: Get frame resolution from resolutionComboBox
 * It sends one signal.         - sendSetResolution(->ModelController): Send current frame resolution
 */
void MainWindow::getResolution(){
    QString resolutionValue = ui->resolutionComboBox->currentText();

    emit sendSetResolution(resolutionValue.toInt());
}

/**
 * @brief MainWindow::getPenSize: Get pen size from penSizeComboBox
 * It sends one signal.         - sendPenSize(->DrawingPanel): Send pen size value
 */
void MainWindow::getPenSize(){
    QString penSizeValue = ui->penSizeComboBox->currentText();

    emit sendPenSize(penSizeValue.toInt());
}

/**
 * @brief MainWindow::getFPSValue: Get FPS value from animationFps
 * It sends one signal.         - sendFPSValue(->PreviewAnimation): Send fps value
 */
void MainWindow::getFPSValue(){
    int fpsValue = 1;

    if(!ui->animationFps->text().isEmpty())
        fpsValue = ui->animationFps->text().toInt();

    emit sendFPSValue(fpsValue);
}

/**
 * @brief MainWindow::takeResolutionValue: Get resolution value from ModelController and set UI as current frame
 * @param fra:  Frame Object that is current frame
 */
void MainWindow::takeResolutionValue(Frame* fra){
    ui->resolutionComboBox->setCurrentIndex(ui->resolutionComboBox->findText(QString::number(fra->resolution)));
}

/**
 * @brief MainWindow::takeImageListFromModel: Get img vector from ModelController
 * It shows every image of frames in scroll area to preview of frames.
 * @param imglist:  QVector<QImage> with all images of frames
 */
void MainWindow::takeImageListFromModel(QVector<QImage> imglist){
    // After delete layout, create layout again and show
    QLayoutItem * item;
    QLayout * sublayout;
    QWidget * widget;

    while ((item = hlayout->takeAt(0))) {
        if ((sublayout = item->layout()) != 0) {
            //If sublayout is there, delete it
        }
        else if ((widget = item->widget()) != 0) {
            widget->hide(); delete widget;
        }
        else {
            delete item;
        }
    }

    delete hlayout;

    // Create a new layout of new images
    hlayout = new QHBoxLayout();

    for(int i = 0; i < imglist.size(); i++){
        QLabel *l = new QLabel();
        l->setPixmap(QPixmap::fromImage(imglist[i].scaled(90, 90)));
        hlayout->addWidget(l);
    }

    scrollWidget->setLayout(hlayout);
}

/**
 * @brief MainWindow::openPreviewWindow: Open preview when Animation button is clicked
 */
void MainWindow::openPreviewWindow(){
    if(prevWindow.isVisible()){
        prevWindow.close();
        prevWindow.show();
    }
    else{
        prevWindow.show();
    }
}

/**
 * @brief MainWindow::on_actionLoad_triggered: Load .ssp file and convert to the JSON type in the
 * modelcontroller class.
 */
void MainWindow::on_actionLoad_triggered(){
    //  getting only ssp file by file dialog
    QString fileSSP = QFileDialog::getOpenFileName(this,tr("Open SSP"),"",tr("SSP Files(*.ssp)"));

    emit callLoad(fileSSP);
}

/**
 * @brief ModelController::save: Save all of the datas as JSON format and file format
 * is .ssp. However, user can also select the .json too.
 * @param fileName: Name of file that user write.
 * @param filePath: Name of path that user select.
 */
void MainWindow::on_actionSave_triggered(){
    //  get full path that is included the path and file name.
    QString file = QFileDialog::getSaveFileName(nullptr, "SAVE", ".", "SSP file (*.ssp);;Json file (*.json)" );
    //  file name that user write
    QString fileName = file.split("/").last();
    //  file path that user select.
    QString filePath= file.section("/",0,-2);

    emit callSave(fileName, filePath);
}

/**
 * @brief MainWindow::clearOptions: Get signal from ModelController and Clear FrameComboBox
 */
void MainWindow::clearOptions(){
    ui->frameComboBox->clear();
}
