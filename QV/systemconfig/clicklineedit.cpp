#include "clicklineedit.h"

ClickLineEdit::ClickLineEdit(QWidget *parent) :
    QLineEdit(parent)
{

}

void ClickLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit SignalClicked();
    }
    QLineEdit::mousePressEvent(event);
}
