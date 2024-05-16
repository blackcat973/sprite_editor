/**
 * @author  MinGyu Jung
 * @review  Simon Padgen
 */

#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QPushButton>
#include <QObject>

class ColorPalette : public QPushButton{
    Q_OBJECT;
public:
    ColorPalette(QWidget* parent = nullptr);
//    virtual ~ColorPalette();
public slots:
    void colorDialog(int buttonNum);
signals:
    void backgroundColor(QColor col, int buttonNum);
};

#endif // COLORPALETTE_H
