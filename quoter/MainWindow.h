#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SimpleParser;

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *m_wnd;

    SimpleParser *m_parser;

public:
    explicit MainWindow(QWidget *parent = 0);
    
public slots:
    void browse();

    void generate();

    void processFromFile(QString filePath);

    void errorOccured(QString message);

};

#endif // MAINWINDOW_H
