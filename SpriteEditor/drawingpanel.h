/**
 * @author  Carly Atwell
 * @review  Simon Padgen
 */

#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRgb>
#include <iostream>
#include "frame.h"

class QPaintEvent;
class QMouseEvent;
class DrawingPanel : public QWidget{
    Q_OBJECT
public:
    explicit DrawingPanel(QWidget *parent = 0);
    ~DrawingPanel();

    void drawPixel(QPoint pt);
    void drawFromFrameArray(Frame* frame);
    void setResolution(int res);
    void setEnabled(bool en);
    void setMirrorEnabled(bool en);
    void setEraserEnabled(bool en);

public slots:
    void clear();
    QColor drawColor();
    void setDrawColor(QColor color);
    void updateDrawingPanelSlot(Frame* frame);
    void changePenSizeSlot(int size);


signals:
    void setPixel(int x, int y, QColor col);
    void sendCurrentImage(QImage img);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

private:
    QColor penColor;
    QPixmap pixmap;
    QImage image;
    int resolution = 128;
    int penSize = 1;
    bool enabled = false;
    bool mirrorEnabled = false;
    bool eraserEnabled = false;
};

#endif // DRAWINGPANEL_H
