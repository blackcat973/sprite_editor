/**
 * @author  MinGyu Jung
 * @review  Simon Padgen, SangYoon Cho, Carly Atwell
 */

#include <QColorDialog>
#include "colorpalette.h"

/**
 * @brief ColorPalette::ColorPalette: constructor for the color palette that
 * implemented the QPushButton.
 * @param parent
 */
ColorPalette::ColorPalette(QWidget* parent) : QPushButton(parent){
}

/**
 * @brief ColorPalette::colorDialog: popping up the color dialog and
 * let user choose the color
 * @param buttonNum: for distinguish which button was selected.
 */
void ColorPalette::colorDialog(int buttonNum){
    //  get color that is selected by user.
    QColor color = QColorDialog::getColor();

    if(color.isValid()){
        emit backgroundColor(color, buttonNum);
    }
}
