#include "LineWidget.h"

void LineWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
    painter.setPen(QPen(QColor::fromRgb(67, 67, 67), 1));   //���û�����ʽ
    painter.drawLine(18, 59, 475, 59);                      //��ֱ��
}
