/**
 * @author  MinGyu Jung
 * @review  Simon Padgen
 */

#ifndef CLICKEVENT_H
#define CLICKEVENT_H
#include <QPushButton>
#include <QMouseEvent>

class ClickEvent : public QPushButton{
    Q_OBJECT
public:
    explicit ClickEvent(QWidget *parent = 0);
private slots:
    void mousePressEvent(QMouseEvent *e);
signals:
    void rightClicked();
    void leftClicked();
public slots:
};

#endif // CLICKEVENT_H
