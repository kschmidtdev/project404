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
 */

#ifndef util_h
#define util_h

#include <sstream>
#include <string>
using namespace std;

// Utility Function to automatically convert most primitives to a STL string
template< typename T >
string toString( const T& toConvert )
{
    ostringstream output;
    output << toConvert;
    return output.str();
}

#ifdef _DEBUG
    #define tacAssert( exp ) assert( exp );
#else
    #define tacAssert( exp )
#endif

#endif  // _util_h_
