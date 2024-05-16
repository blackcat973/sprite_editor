/**
 * @author  SangYoon Cho
 * @review  Carly Atwell
 */

#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include <QVector>
#include <QImage>
#include <QTimer>

namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWindow(QWidget *parent = nullptr);
    ~PreviewWindow();

public slots:
    void getImageListFromModel(QVector<QImage> imglist);
    void showPreviewAnimation();
    void setFramePerSecond(int framepersecond);

private:
    Ui::PreviewWindow *ui;
    void activeAnimation();

    QVector<QImage> imageListFromModel;
    QTimer delayTimer;

    int FPS;
    int count;
};

#endif // PREVIEWWINDOW_H
