#ifndef CANNONFIELD_H
#define CANNONFIELD_H

#include <qwidget.h>

class CannonField : public QWidget
{
    Q_OBJECT
public:
    CannonField(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    int angle() const { return ang; }
    int force() const { return f; }
    void  shoot();
    QSizePolicy sizePolicy() const;

public slots:
    void setAngle( int degrees );
    void setForce( int newton );
    void  moveShot();

signals:
    void angleChanged( int );
    void forceChanged( int );

protected:
    void paintEvent( QPaintEvent * );
    QRect cannonRect() const;
    QRect shotRect() const;

private:
    void  paintShot( QPainter * );
    int ang;
    int f;
    int timerCount;
    QTimer * autoShootTimer;
    float shoot_ang;
    float shoot_f;
};

#endif // CANNONFIELD_H
