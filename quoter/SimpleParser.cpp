#include "SimpleParser.h"

#include <QObject>
#include <QDebug>

SimpleParser::SimpleParser( bool appendPlus, QObject *parent ) :
    QObject( parent ),
    m_appendPlus( appendPlus )
{
}

QString SimpleParser::processText(const wchar_t *data, quint64 size)
{
    QString tempStr = "";
    QString spaceAggr = "";
    try {
        for( int i = 0; i < size; ) {
            quint64 lineLen = 0;
            bool isCtrlM = false;
            bool started = false;
            while( i < size ) {
                if( ( i + 1 ) < size
                        && data[ i ] == '\r'
                        && data[ i + 1] == '\n' ) {
                    ++ ( ++ i );
                    isCtrlM = true;
                    break;
                }
                else if( data[ i ] == '\n' ) {
                    isCtrlM =  false;
                    ++ i;
                    break;
                }
                if( ! started ) {
                    if( iswblank( data[ i ] )) {
                        spaceAggr += data[ i ];
                        ++ i;
                        continue;
                    }
                    tempStr.append( "\"" );
                    started = true;
                }
                tempStr += spaceAggr;
                if( data[ i ] == '"' || data[ i ] == '\\') {
                    tempStr += "\\";
                    tempStr += data[ i ];
                }
                else {
                    tempStr += data[ i ];
                }
                spaceAggr.clear();
                ++ i;
                ++ lineLen;
            }
            spaceAggr.clear();
            if( lineLen ) {

                tempStr.append( "\"")
                       .append( isCtrlM ?
                                    m_appendPlus ? " + \r\n" : "\r\n"
                                  : m_appendPlus ? " + \n"   : "\n" );

            }
            else {
                tempStr.append( isCtrlM ? "\r\n" : "\n" );
            }
        }
        if( m_appendPlus ) {
            tempStr.remove( tempStr.lastIndexOf( '+'), 1);
        }
    } catch( ... ) {
        emit errorOccured( "Error occured while parsing" );
        throw -1;
    }

    return tempStr;
}



QString SimpleParser::processText( QString input )
{
    wchar_t *data = new wchar_t[ input.size() ];
    input.toWCharArray( data );
    return processText( data, input.size() );
}




void SimpleParser::appendPlus( bool value )
{
    m_appendPlus = value;
}
