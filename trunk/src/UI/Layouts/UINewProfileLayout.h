/**
 * Layout used to create a new profile
 *
 * #include "UINewProfileLayout.h"
 *
 * Layout used to create a new profile
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Andrew Osborne, March 21 2007, Commented out Process Event (part of debug)
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 23 2007, Added proper functionality, added mAlpha, mMenu
 * Karl Schmidt, March 31 2007   | Removed functionality that was moved to UIAlphabetGrid, removed instructional
                                   text that is no longer needed
 * Andrew Osborne, April 5 2007 | Added OnLoad
 */

#ifndef UINewProfileLayout_h
#define UINewProfileLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>


// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIAlphabetGrid;
class UIText;

class UINewProfileLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UINewProfileLayout(void);

    /**
     * Destructor.
	 */
    ~UINewProfileLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Overwrite OnLoad function - method called when layout is being intitialized for viewing
     */
    virtual void OnLoad(void);

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    UIAlphabetGrid *mAlpha;
    UIText* mHelperTxt;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UINewProfileLayout_h_
