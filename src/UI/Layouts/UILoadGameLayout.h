/**
 * Layout that prompts user to select saved game.
 *
 * #include "UILoadGameLayout.h"
 *
 * Layout that prompts user to select saved game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added proper UI functionality (Menu with options)
 * Karl Schmidt, March 25 2007   | Added functionality for loading savegames, and also going back to the previous menu
 */

#ifndef UILoadGameLayout_h
#define UILoadGameLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIMenu;

class UILoadGameLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UILoadGameLayout(void);


    /**
     * Destructor.
	 */
    ~UILoadGameLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Overwrites OnLoad operation
     */
    virtual void OnLoad(void);

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    UIMenu* mMenu;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UILoadGameLayout_h_
