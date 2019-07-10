#include "cannonfield.h"
#include "qpainter.h"
#include "QPaintEvent"
#include "QPixmap"
#include "math.h"
#include "QTimer"
#include "QDebug"

CannonField::CannonField(QWidget *parent, Qt::WindowFlags flag)
    :QWidget (parent, flag)
{
    setMinimumSize(150, 150);
    setMaximumSize(200, 200);
    ang = 45;
    f = 0;
    timerCount = 0;
    autoShootTimer = new QTimer(this);
    connect( autoShootTimer, SIGNAL(timeout()),
             this, SLOT(moveShot()) );
    shoot_ang = 0;
    shoot_f = 0;
    setPalette( QPalette( QColor( 200, 200, 200) ) );
    setAutoFillBackground(true);
}

void CannonField::shoot()
{
    if ( autoShootTimer->isActive() )
        return;
    timerCount = 0;
    shoot_ang = ang;
    shoot_f = f;
    qDebug() << "start to shoot";
    autoShootTimer->start( 50 );
}

void CannonField::moveShot()
{
    QRegion r( shotRect() );
    timerCount++;

    QRect shotR = shotRect();

    if ( shotR.x() > width() || shotR.y() > height() )
        autoShootTimer->stop();
    else
        r = r.united(QRegion(shotR));
    repaint( r );
}

void CannonField::setAngle( int degrees )
{
    if ( degrees < 5 )
        degrees = 5;
    if ( degrees > 70 )
        degrees = 70;
    if ( ang == degrees )
        return;
    ang = degrees;
    repaint(cannonRect());
    emit angleChanged( ang );
}

void CannonField::setForce( int newton )
{
    if ( newton < 0 )
        newton = 0;
    if ( f == newton )
        return;
    f = newton;
    emit forceChanged( f );
}

QRect CannonField::cannonRect() const
{
    QRect r( 0, 0, 50, 50 );
    r.moveBottomLeft( rect().bottomLeft() );
    return r;
}

void CannonField::paintShot( QPainter *p )
{
    p->setBrush( Qt::black );
    p->setPen( Qt::PenStyle::NoPen );
    p->drawRect( shotRect() );
}

QRect CannonField::shotRect() const
{
    const double gravity = 4;

    double time      = timerCount / 4.0;
    double velocity  = shoot_f;
    double radians   = shoot_ang*3.14159265/180;

    double velx      = velocity*cos( radians );
    double vely      = velocity*sin( radians );
    double x0        = ( /*barrelRect.right()*/  + 5 )*cos(radians);
    double y0        = ( /*barrelRect.right()*/  + 5 )*sin(radians);
    double x         = x0 + velx*time;
    double y         = y0 + vely*time - 0.5*gravity*time*time;

    QRect r = QRect( 0, 0, 6, 6 );
    r.moveCenter( QPoint( qRound(x), height() - 1 - qRound(y) ) );
    return r;
}

void CannonField::paintEvent( QPaintEvent *qevent)
{
    QPainter painter( this );
    if (qevent->rect().intersects( cannonRect() ) ) {
        QString s = "Angle: " + QString::number( ang );
        painter.drawText( 100, 100, s);

        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::PenStyle::NoPen);
        painter.translate(0, rect().bottom());
        painter.drawPie(QRect(-35, -35, 70, 70), 0, 90*16);
        painter.rotate(-ang);
        painter.drawRect(QRect(33, -4, 10, 8));
    }
    if ( autoShootTimer->isActive() &&
         qevent->rect().intersects( shotRect() ) )
        paintShot( &painter );
}
