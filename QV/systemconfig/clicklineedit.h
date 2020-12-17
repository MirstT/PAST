#ifndef CLICKLINEEDIT_H
#define CLICKLINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>


class ClickLineEdit: public QLineEdit
{
    Q_OBJECT
public:
   ClickLineEdit();

    explicit ClickLineEdit(QWidget *parent = nullptr);
protected:
    //重写mousePressEvent事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void SignalClicked();

};  
#endif // ClickLineEdit_H
