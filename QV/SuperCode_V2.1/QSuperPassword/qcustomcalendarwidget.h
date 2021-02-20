#pragma once
//qcustomcalendarwidget.h

#ifndef QCUSTOMCALENDARWIDGET_H
#define QCUSTOMCALENDARWIDGET_H

#include <QCalendarWidget>

class QPushButton;
class QLabel;
class QCustomCalendarWidget : public QCalendarWidget
{
    Q_OBJECT

public:
    QCustomCalendarWidget(QWidget* parent);
    ~QCustomCalendarWidget();

private:
    void initControl();
    void initTopWidget();
    void initBottomWidget();
    void setDataLabelTimeText(int year, int month);

signals:
    void signalSetCalendarTime(const QDate& data);

private slots:
    void onbtnClicked();

protected:
    void paintCell(QPainter* painter, const QRect& rect, const QDate& date) const;

private:
    QPushButton* m_leftYearBtn;
    QPushButton* m_leftMonthBtn;

    QPushButton* m_rightYearBtn;
    QPushButton* m_rightMonthBtn;

    QPushButton* m_ensureBtn;
    QPushButton* m_toDayBtn;

    QLabel* m_dataLabel;
};
#endif