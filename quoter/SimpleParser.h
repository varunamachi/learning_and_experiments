#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

#include <QString>
#include <QObject>

class SimpleParser : public QObject
{
    Q_OBJECT

    bool m_appendPlus;

public:
    SimpleParser(bool appendPlus, QObject *parent = 0);

    QString processText(const wchar_t *data, quint64 size );

    QString processText( QString input );

signals:

    void errorOccured( QString message );

public slots:

    void appendPlus( bool value );

};

#endif // SIMPLEPARSER_H
