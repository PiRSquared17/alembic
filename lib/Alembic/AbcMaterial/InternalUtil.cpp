//-*****************************************************************************
//
// Copyright (c) 2009-2012,
//  Sony Pictures Imageworks Inc. and
//  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Sony Pictures Imageworks, nor
// Industrial Light & Magic, nor the names of their contributors may be used
// to endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-*****************************************************************************

#include "InternalUtil.h"

#include <Alembic/Util/All.h>

#include <sstream>

namespace Alembic {
namespace AbcMaterial {
namespace ALEMBIC_VERSION_NS {
namespace Util {

std::string
buildTargetName( const std::string & target,
                 const std::string & shaderType,
                 const std::string & suffix )
{
    std::string name = target;
    name += ".";
    name += shaderType;

    if (!suffix.empty())
    {
        name += "." + suffix;
    }

    return name;
}


void validateName( const std::string & name,
                   const std::string & exceptionVariableName )
{
    if ( name.find('.') != std::string::npos ||
         name.find('/') != std::string::npos )
    {
        ABC_THROW( "invalid name for " << exceptionVariableName <<
                   ":" << name );
    }
}


void split_tokens( const std::string & value,
                   std::vector<std::string> & result,
                   size_t maxSplit )
{
    result.clear();

    if ( value.empty() )
    {
        result.push_back("");
        return;
    }

    size_t pos = 0;

    for ( size_t i = 0;
        ( maxSplit == 0 || i < maxSplit ) && pos < value.size(); ++i )
    {
        size_t nextDotIndex = value.find('.', pos);

        if ( nextDotIndex == std::string::npos )
        {
            break;
        }

        result.push_back( value.substr( pos, nextDotIndex-pos ) );

        if ( nextDotIndex == value.size() - 1 )
        {
            result.push_back( "" );
        }

        pos = nextDotIndex + 1;
    }

    if ( pos < value.size() )
    {
        result.push_back( value.substr( pos ) );
    }
}

} // End namespace Util
} // End namespace ALEMBIC_VERSION_NS
} // End namespace AbcGeom
} // End namespace Alembic