#pragma once

#include "Param.hpp"
#include "Field.hpp"

namespace Amachi { namespace BinData { namespace Data {

class Value : public Param
{
public:
    Value( const std::string &name,
           const std::string &displayName )
        : Param( name, displayName )
    {

    }


private:


};


template< typename ParamType >
class ValueEx : public ParamType
{

};


} } }
