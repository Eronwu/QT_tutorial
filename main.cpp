#include "mainwindow.h"
#include <QApplication>

#include "qpushbutton.h"
#include "qfont.h"
#include "QVBoxLayout"
#include "qlcdnumber.h"
#include "qslider.h"

class TestWidget : public QWidget
{
public:
    TestWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};

TestWidget::TestWidget(QWidget *parent, Qt::WindowFlags f)
          :QWidget (parent, f)
{
    setMinimumSize(100, 100);
    setMaximumSize(200, 200);

    QPushButton *buttonQuit = new QPushButton("WQUIT", this);
    buttonQuit->setGeometry(50, 10, 50, 30);
    buttonQuit->resize(100, 50);
    buttonQuit->setFont(QFont("Times", 18, QFont::Thin));

    connect(buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QLCDNumber *lcd = new QLCDNumber(2, this);
    lcd->display(50);
    QSlider *slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setRange(0, 99);
    slider->setValue(50);
    slider->setGeometry(20, 100, 150, 30);

    connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

//    QVBoxLayout vlayout;
//    vlayout.addWidget(buttonQuit);
//    vlayout.addWidget(lcd);
//    vlayout.addWidget(slider);
//    this->setLayout(&vlayout);
}

class Test2Widget : public QVBoxLayout
{
public:
    Test2Widget(QWidget *parent = nullptr);
};

Test2Widget::Test2Widget(QWidget *parent)
           :QVBoxLayout (parent)
{
    QPushButton *buttonQuit = new QPushButton("LQUIT", parent);
    buttonQuit->setFont(QFont("Times", 18, QFont::Thin));
    connect(buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QLCDNumber *lcd = new QLCDNumber(2, parent);
    QSlider *slider = new QSlider(Qt::Orientation::Horizontal, parent);
    slider->setRange(0, 99);
    slider->setValue(50);

    connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int testCase = 2;

    if (testCase == 0) {
        MainWindow w;
        w.show();
        return a.exec();
    } else if (testCase == 1) {
        //QVBox box; the class is deprecated
        QWidget window;
        window.resize(400, 200);
        QVBoxLayout vlayout;

        QPushButton buttonStart("START", nullptr);
        QPushButton buttonQuit("QUIT", nullptr);
        buttonStart.resize(80, 40);
        buttonQuit.resize(80, 40);
        buttonStart.setFont((QFont("Times", 18, QFont::Bold)));
        buttonQuit.setFont(QFont("Times", 18, QFont::Bold));
        QObject::connect(&buttonQuit, SIGNAL(clicked()), &a, SLOT(quit()));

        vlayout.addWidget(&buttonStart);
        vlayout.addWidget(&buttonQuit);

        //a.setMainWidget( &hello ); the function is deprecated
        //buttonQuit.show();
        window.setLayout(&vlayout);
        window.show();
        return a.exec();
    } else if (testCase == 2) {
        TestWidget testw;
        testw.show();
        return a.exec();
    } else if (testCase == 3) {
        Test2Widget test2l;
        QWidget window;
        window.setLayout(&test2l);
        window.show();
        return a.exec();
    }

    return 0;
}
