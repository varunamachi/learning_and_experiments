#include "PlotterWidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QSize>
#include <QDebug>
#include <QThread>


PlotterWidget::PlotterWidget(int width,
                             int height,
                             bool withNegetive,
                             QWidget *parent) :
    QWidget(parent),
    m_pixelsPerXBlock( 30 ),
    m_maxHistory( 1000 ),
    m_currentIndex( 0 ),
    m_curMax( 100 ),
    m_autoAdjust( true ),
    m_showYLines( true ),
    m_showXLines( true ),
    m_showValueString( true ),
    m_withNegetive( withNegetive )

{
    m_size = new QSize( width, height );
    m_yFactor = static_cast< int >( height / m_curMax );
    m_valuesPerView = static_cast< int > (width / m_pixelsPerXBlock );
    m_buffer = new QPixmap( *m_size );
    m_inSnapshotMode = false;
    initWidget();
}


void PlotterWidget::initWidget()
{
    this->setMaximumSize( *m_size );
    this->setAutoFillBackground( true );
    QPalette palt;
    palt.setColor( QPalette::Background, Qt::black);
    this->setPalette( palt );
}

PlotterWidget::~PlotterWidget()
{
    delete m_timer;
    delete m_size;
}


QSize PlotterWidget::sizeHint()
{
    return *m_size;
}


void PlotterWidget::setValue( int value )
{
    m_values << value;
    if( m_autoAdjust && qAbs( value ) > m_curMax ) {
        m_curMax = qAbs( value );
        m_yFactor = (( float )this->height() /
                     ( m_withNegetive ? m_curMax * 2 : m_curMax ));
    }
    if( m_values.size() > m_valuesPerView ){
        ++ m_currentIndex;
    }
    else if( m_values.size() == m_maxHistory ) {
        m_values.removeFirst();
        m_currentIndex = m_maxHistory - m_valuesPerView;
    }
    if( ! m_inSnapshotMode ) {
        delete m_buffer;
        m_buffer = new QPixmap( *m_size );
        writeToBuffer( & m_values, m_currentIndex, m_valuesPerView );
    }

}

void PlotterWidget::writeToBuffer( QList< int > *values,
                                   int startIndex,
                                   int numValues )
{
    static int xLineStart = 0;
    QPainter painter( m_buffer );
    painter.setRenderHint( QPainter::Antialiasing );

    int x1Pos = 0;
    int x2Pos = m_pixelsPerXBlock;
    int y1Pos = 0, y2Pos = 0;
    if( m_withNegetive ) {
        painter.setPen( QPen( QBrush( Qt::gray ), 2 ));
        painter.drawLine( 0, this->height() / 2,
                          m_buffer->width(), this->height() / 2);
    }
    painter.setPen( QPen( QBrush( Qt::lightGray ), 0.3 ) );
    if( m_showYLines ) {
        if( startIndex != 0 ) {
            xLineStart = ( ++ xLineStart ) % 2;
        }
        for( int i = ( xLineStart * m_pixelsPerXBlock );
             i < ( m_buffer->width() - ( xLineStart * m_pixelsPerXBlock ));
             i += m_pixelsPerXBlock * 2) {
            painter.drawLine( i, 0, i, this->height() );
        }
    }
    if( m_showXLines ) {
        if( m_withNegetive ) {
            for( int i = 0; i < m_size->height() ; i += ( 10 * m_yFactor )) {
//                painter.drawLine( 0, i, this->width(), i  );
                painter.drawLine( 0, i, m_buffer->width(), ++i );
            }
        }
        else {
            for( int i = 0; i < m_size->height() ; i += ( 10 * m_yFactor )) {
                painter.drawLine( 0, i, m_buffer->width(), i  );
            }
        }
    }
    int height = m_withNegetive ? this->height() / 2 : this->height();
//    int until = values->size() - 1;
//    if( m_inSnapshotMode ) {
//        until =  ( startIndex + m_valuesPerView ) < ( values->size() - 1 ) ?
//                        ( startIndex + m_valuesPerView ): values->size() - 1;
//    }

    numValues = numValues < values->size() ? ( numValues - 1 ) :
                                             ( values->size() - 1 );
    for( int i = startIndex; i < ( startIndex + numValues ); ++ i) {
        painter.setPen( QPen( QBrush( Qt::green), 2 ));
        y1Pos = static_cast< int >(
                    height - ( values->at( i ) * m_yFactor ));
        y2Pos = static_cast< int >(
                    height - ( values->at( i + 1 ) * m_yFactor ));
        painter.drawLine( x1Pos, y1Pos, x2Pos, y2Pos );
        x1Pos += m_pixelsPerXBlock;
        x2Pos += m_pixelsPerXBlock;
        painter.setPen( Qt::yellow );
        painter.drawEllipse( x1Pos -2, y2Pos - 2, 4, 4 );
        if( m_showValueString ) {
            painter.setPen( Qt::red );
            painter.drawText( x1Pos, y2Pos, QString("%1").arg(
                                  values->at( i + 1 ) + 5 ));
        }
    }
    update();
}


void PlotterWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter( this );
    if( ! m_inSnapshotMode ) {
        painter.drawPixmap( 0, 0, *m_buffer );
    }
    else {
        QRect sourceRect = QRect( m_snapshotStartPixel, 0,
                                  m_size->width(), this->height() );
        painter.drawPixmap( this->rect(), *m_buffer, sourceRect );
    }
}


void PlotterWidget::resizeEvent( QResizeEvent *evt )
{
    if( m_autoAdjust ) {
        m_yFactor = (( float )this->height() /
                     ( m_withNegetive ? m_curMax * 2 : m_curMax ));
    }
    if( m_inSnapshotMode ) {
        delete m_buffer;
        int newBufferSize = m_pixelsPerXBlock * m_values.size();
        m_buffer = new QPixmap( newBufferSize, m_size->height() );
        writeToBuffer( &m_values, 0, m_values.size() );
    }

}


void PlotterWidget::mousePressEvent( QMouseEvent *evt )
{
    if( evt->button() == Qt::MidButton ) {
        if( m_inSnapshotMode ) {
            m_inSnapshotMode = false;
            m_dragStartX = 0;
            m_snapshotStartPixel = 0;
            delete m_buffer;
            m_buffer = new QPixmap( *m_size );
        }
        else {
            m_inSnapshotMode = true;
            m_snapshotStartPixel = m_currentIndex * m_pixelsPerXBlock;
            delete m_buffer;
            int newBufferSize = m_pixelsPerXBlock * m_values.size();
            m_buffer = new QPixmap( newBufferSize, m_size->height() );
            writeToBuffer( &m_values, 0, m_values.size() );
        }
    }
    m_dragStartX = evt->x();
}


void PlotterWidget::mouseMoveEvent( QMouseEvent *evt ) {
    int drag = evt->x() - m_dragStartX;
    int newStart = m_snapshotStartPixel - drag;
    if(( ( newStart + m_size->width() ) < m_buffer->width() )
       && newStart >= 0 ) {
        m_dragStartX = evt->x();
        m_snapshotStartPixel -= drag;
        update();
    }
}

//void PlotterWidget::mouseReleaseEvent( QMouseEvent *evt )
//{
////    m_snapshot.clear();
////    m_inSnapshotMode = false;
////    m_snapshotIndex = 0;
//}









