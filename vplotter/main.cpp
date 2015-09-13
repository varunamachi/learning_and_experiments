#include <QApplication>
#include "MainWindow.h"
#include "PlotterWidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *pw = new MainWindow();
    pw->show();
    
    return a.exec();
}


