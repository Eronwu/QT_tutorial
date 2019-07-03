#include "mainwindow.h"
#include <QApplication>

#include "testwidget.h"

TestWidget::TestWidget(QWidget *parent, Qt::WindowFlags f)
          :QWidget (parent, f)
{
    setMinimumSize(200, 200);
    setMaximumSize(200, 200);

    QPushButton *buttonQuit = new QPushButton("WQUIT", this);
    buttonQuit->setGeometry(50, 10, 50, 30);
    buttonQuit->resize(100, 50);
    buttonQuit->setFont(QFont("Times", 18, QFont::Thin));

    connect(buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    lcd = new QLCDNumber(2, this);
    lcd->display(50);
    slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setRange(0, 99);
    slider->setValue(50);
    slider->setGeometry(20, 100, 150, 30);

    connect( slider, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)) );
//    connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

//    QVBoxLayout vlayout;
//    vlayout.addWidget(buttonQuit);
//    vlayout.addWidget(lcd);
//    vlayout.addWidget(slider);
//    this->setLayout(&vlayout);
}

void TestWidget::display(int v)
{
    lcd->display(v);
}

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

    int testCase = 4;

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
    } else if (testCase == 3) { // fail
        Test2Widget test2l;
        QWidget window;
        window.setLayout(&test2l);
        window.show();
        return a.exec();
    } else if (testCase == 4) {
        QGridLayout gridLayout;
        TestWidget *previous = nullptr;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                TestWidget *tw = new TestWidget();
                gridLayout.addWidget(tw, row, col);
                if (previous != nullptr)
                    QObject::connect(tw, SIGNAL(valueChanged(int)), previous, SLOT(display(int)));
                previous = tw;

            }
        }
        QWidget window;
        window.setLayout(&gridLayout);
        window.show();
        return a.exec();
    }

    return 0;
}
