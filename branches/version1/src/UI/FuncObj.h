/**
 * An object that contains a single function
 *
 * #include "FuncObj.h"
 *
 * Used in the UI for determining what action to take when a particular button is pressed.  The object
 * is created to avoid using function pointers.
 *
 * @see UIMenu, UIGrid
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007, Initial Creation
 */

#ifndef FuncObj_h
#define FuncObj_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class FuncObj
{
public:
// LIFECYCLE
// OPERATORS
// OPERATIONS

    virtual void operator()(void) = 0;

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _FuncObj_h_
