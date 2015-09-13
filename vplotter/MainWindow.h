#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

#include "PlotterWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    QTimer *m_timer;

    PlotterWidget *m_plotter;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void onTimeOut();


};

#endif // MAINWINDOW_H
