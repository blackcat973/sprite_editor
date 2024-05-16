#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include "qgraphicsscene.h"
#include "colorpalette.h"
#include "clickevent.h"
#include "modelcontroller.h"
#include "drawingpanel.h"
#include "previewwindow.h"
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(ModelController& model, ColorPalette& color, QWidget *parent = nullptr);

    ~MainWindow();
    ClickEvent *buttonTest0;
    ClickEvent *buttonTest1;
    ClickEvent *buttonTest2;
    ClickEvent *buttonTest3;
    ClickEvent *buttonTest4;
    ClickEvent *buttonTest5;
    ClickEvent *buttonTest6;
    ClickEvent *buttonTest7;
    ClickEvent *buttonTest8;
    ClickEvent *clickedButton;
    QVector<ClickEvent*> buttonList;

public slots:
    void takeAddIndexNum(int currIndex, Frame* fra);
    void takeDeleteIndexNum(int currIndex);
    void takeResolutionValue(Frame* fra);
    void takeImageListFromModel(QVector<QImage> imglist);
    void onLeftClicked(int indexNum);
    void onRightClicked(int indexNum);
    void backgroundColor(QColor color1, int buttonNum);
    void getResolution();
    void getPenSize();
    void getFrameName();
    void clearOptions();
    void getFPSValue();

signals:
    void rightClick();
    void leftClick();
    void sendSetResolution(int res);
    void sendPenSize(int sz);
    void sendGetCurrFrameIndex(int fra);
    void sendSetFrameName(QString name);
    void sendFPSValue(int fps);
    void colorSelected(int idx);
    void getColor(int buttonNum);
    void colorUpdate(QColor color, int buttonNum);
    void callLoad(QString fileName);
    void callSave(QString fileName, QString filePath);

private slots:

    void on_actionLoad_triggered();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    void drawToolButtonClickedSlot();
    void mirrorDrawToolButtonClickedSlot();
    void eraseToolButtonClickedSlot();
    void xFlipToolButtonClickedSlot();
    void yFlipToolButtonClickedSlot();
    void rotateToolButtonClickedSlot();
    void frameComboBoxCurrentIndexChangedSlot();
    void getCurrFrame();
    void drawRectangle();
    void enterkeyPressEvent(QKeyEvent *evnet);
    void openPreviewWindow();

    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QHBoxLayout *hlayout;
    QWidget *scrollWidget;

    DrawingPanel *drawingPanel;
    PreviewWindow prevWindow;

};
#endif // MAINWINDOW_H
