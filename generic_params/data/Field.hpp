#pragma once

#include <string>
#include <cstdint>
#include <memory>

#include "Param.hpp"


namespace Amachi { namespace BinData { namespace Data {


class Field : public Param
{
public:
    typedef std::shared_ptr< Field > Ptr;

    Field( const std::string &name,
           const std::string &displayName,
           std::uint8_t lsb,
           std::uint8_t size,
           std::uint32_t mask )
        : Param( name, displayName )
        , m_lsb( lsb )
        , m_size( size )
        , m_mask( mask )
    {

    }

    const std::uint8_t lsb() const
    {
        return m_lsb;
    }

    const std::uint8_t size() const
    {
        return m_size;
    }

    const std::uint32_t mask() const
    {
        return m_mask;
    }

private:
    std::uint8_t m_lsb;

    std::uint8_t m_size;

    std::uint32_t m_mask;

};

template< typename ParamType >
class FieldEx : public ParamType
{

};

} } }
