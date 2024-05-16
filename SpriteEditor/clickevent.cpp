/**
 * @author  MinGyu Jung
 * @review  Simon Padgen, SangYoon Cho
 */

#include "clickevent.h"

/**
 * @brief ClickEvent::ClickEvent: Constructor for ClickEvent that
 * implemented the QPushButton
 * @param parent
 */
ClickEvent::ClickEvent(QWidget *parent) : QPushButton(parent){
}

/**
 * @brief ClickEvent::mousePressEvent: mouse press event for
 * recognizing left and right click.
 * @param e: Mouse event.
 */
void ClickEvent::mousePressEvent(QMouseEvent *e){
    if(e->button()==Qt::RightButton){
       emit rightClicked();
    }else if(e-> button()==Qt::LeftButton){
        emit leftClicked();
    }
}
