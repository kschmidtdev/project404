/**
 * This is not a class, just a collection of utility functions
 *
 * #include "util.h"
 *
 * See short description
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 11 2007 | Initial creation
 * Karl Schmidt, March 12 2007 | Added assert logging (useful!)
 */

#ifndef util_h
#define util_h

#include <Logger.h>

#include <sstream>
#include <string>

// Utility Function to automatically convert most primitives to a STL string
template< typename T >
std::string toString( const T& toConvert )
{
    std::ostringstream output;
    output << toConvert;
    return output.str();
}

#ifdef _DEBUG
    #include <mmgr/mmgr.h>
    #define tacAssert( exp ) if( !(exp) ) { LogError("Assert hit"); } assert( exp );
#else
    #define tacAssert( exp )
#endif

#endif  // _util_h_
