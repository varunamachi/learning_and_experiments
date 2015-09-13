#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SimpleParser.h"

#include <QDebug>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_parser( new SimpleParser( false, parent ))
{
    m_wnd = new Ui::MainWindow();
    m_wnd->setupUi( this );
    m_wnd->inputText->setVisible( false );
    m_wnd->inputText->
    connect( m_wnd->generateButton, SIGNAL( clicked() ),
             this, SLOT( generate() ));
    connect( m_wnd->browseFile, SIGNAL( clicked() ),
             this, SLOT( browse() ));
    connect( m_parser, SIGNAL( errorOccured(QString) ) ,
             this, SLOT( errorOccured( QString )));
    connect( m_wnd->appendPlusButton, SIGNAL( toggled(bool)),
             m_parser, SLOT( appendPlus(bool) ));
}




void MainWindow::processFromFile( QString filePath )
{
    QFile file( filePath );


    if( file.exists() ) {
        file.open( QIODevice::ReadOnly );
        QTextStream stream( &file );
        QString content = stream.readAll();
        QString output = m_parser->processText( content );
        m_wnd->outputText->setText( output );
    }
    else {
        m_wnd->errorLable->setText( "<font color = red> Error while "
                                    "reading file");
    }
}

void MainWindow::errorOccured( QString message )
{
    if( ! message.isEmpty() ) {
        m_wnd->errorLable->setText( QString() + "<font color='red'>"+ message +
                                    "<\\font>");
    }
}





void MainWindow::browse() {
    QString path = QFileDialog::getOpenFileName();
    if( ! path.isEmpty() ) {
        m_wnd->filePath->setText( path );
    }
}



void MainWindow::generate()
{
    try {
        if( m_wnd->fileButton->isChecked() ) {
            QString path = m_wnd->filePath->text().trimmed();
            if( path.isEmpty() ) {
                path = QFileDialog::getOpenFileName();
                if( path.isEmpty() ) {
                    return;
                }
            }
            m_wnd->filePath->setText( path );
            processFromFile( path );
        }
        else {
            QString output =
                    m_parser->processText( m_wnd->inputText->toPlainText() );
            if( ! output.isEmpty() ) {
                m_wnd->outputText->setText( output );
            }
        }
    } catch( ... ) {
        return;
    }
    return;
}





