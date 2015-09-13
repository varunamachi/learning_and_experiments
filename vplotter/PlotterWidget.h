#ifndef PLOTTERWIDGET_H
#define PLOTTERWIDGET_H

#include <QWidget>
#include <QColor>
#include <QTimer>
#include <QList>
#include <QGraphicsView>

class PlotterWidget : public QWidget
{
    Q_OBJECT

    float m_yFactor;

    int m_pixelsPerXBlock;

    int m_maxHistory;

    int m_valuesPerView;

    int m_currentIndex;

    int m_curMax;

    bool m_autoAdjust;

    bool m_showYLines;

    bool m_showXLines;

    bool m_showValueString;

    bool m_withNegetive;


    int m_dragStartX;

    QPixmap *m_buffer;

    QList< int > m_values;

    int m_snapshotStartPixel;


    int m_snapshotIndex;

    bool m_inSnapshotMode;

    QList< int > m_snapshot;



    QSize *m_size;

    QTimer *m_timer;

    void initWidget();

protected:
    void paintEvent( QPaintEvent *event );

    void resizeEvent( QResizeEvent * evt );

    void mouseMoveEvent( QMouseEvent *evt );

    void mousePressEvent( QMouseEvent *evt );

//    void mouseReleaseEvent( QMouseEvent *evt );


public:
    explicit PlotterWidget(int width,
                           int height,
                           bool autoAdj = false,
                           QWidget *parent = 0);

    virtual ~PlotterWidget();

    QSize sizeHint();

    void setValue( int value );
    
private slots:


    void writeToBuffer( QList< int > *values,
                        int startIndex,
                        int numValues );

    
};

#endif // PLOTTERWIDGET_H
