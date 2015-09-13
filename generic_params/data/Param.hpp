#pragma once

#include <string>

namespace Amachi { namespace BinData { namespace Data {

class Param
{
public:
    Param( const std::string &name,
           const std::string &displayName )
        : m_name( name )
        , m_displayName( displayName )
    {

    }

    const std::string & name() const
    {
        return m_name;
    }

    const std::string & displayName() const
    {
        return m_displayName();
    }

private:
    std::string m_name;

    std::string m_displayName;

};

} } }
