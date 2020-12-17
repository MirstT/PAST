#ifndef LINEWIDGET_H
#define LINEWIDGET_H
#include <QWidget>
#include <QPainter>

class LineWidget : public QWidget
{
protected:
    virtual void paintEvent(QPaintEvent* event);;

};

#endif