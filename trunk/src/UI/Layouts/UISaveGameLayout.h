/**
 * Layout to Save Game.
 *
 * #include "UISaveGameLayout.h"
 *
 * Layout to Save Game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added proper menu functionality, removed ProcessEvent, added OnLoad
 * Andrew Osborne, March 23 2007 | Made small change to comply with other changes Karl has made to 'include' format
 */

#ifndef UISaveGameLayout_h
#define UISaveGameLayout_h

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

class UISaveGameLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UISaveGameLayout(void);

    /**
     * Destructor.
	 */
    ~UISaveGameLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Listens for Key Press from User
    */
    //virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

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

#endif  // _UISaveGameLayout_h_
