#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include "qpushbutton.h"
#include "qfont.h"
#include "QVBoxLayout"
#include "qlcdnumber.h"
#include "qslider.h"
#include "QGridLayout"

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QLCDNumber *lcd;
    QSlider *slider;
    void setRange(int minVal, int maxVal);
public slots:
    void display(int);
signals:
    void valueChanged(int);
};

class Test2Widget : public QVBoxLayout
{
    Q_OBJECT
public:
    Test2Widget(QWidget *parent = nullptr);
};
#endif // TESTWIDGET_H
