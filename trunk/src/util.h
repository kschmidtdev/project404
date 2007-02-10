/**
 * A one line description of the class.
 *
 * #include "util.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
 */

#ifndef util_h
#define util_h

#ifdef _DEBUG
    #define tacAssert( exp ) assert( exp );
#else
    #define tacAssert( exp )
#endif

#endif  // _util_h_
