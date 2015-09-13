#include "MainWindow.h"
#include "PlotterWidget.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QSize>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_timer = new QTimer();
    m_timer->setInterval( 100 );
    m_plotter = new PlotterWidget( 1024, 1024, true, this );
    connect( m_timer, SIGNAL( timeout() ) , this, SLOT( onTimeOut() ));
    m_timer->start();
    this->setLayout( new QHBoxLayout() );
    this->setCentralWidget( m_plotter );
}

void MainWindow::onTimeOut()
{
    static int angle = 0;
//    if( qrand() % 2 ) {
//        m_plotter->setValue( qrand() % 500 - 250 );
//    }
//    else {
        angle = ( angle + 10 ) % 360;
        double rad = (( double ) 3.14 * angle ) / 180;
        m_plotter->setValue( sin( rad ) * angle );
//    }
//    angle += 10;
//    angle = angle % 500;
//    m_plotter->setValue( angle );
}

MainWindow::~MainWindow()
{
    delete m_plotter;
    delete m_timer;
}
