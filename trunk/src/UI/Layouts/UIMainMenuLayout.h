/**
 * The class that represents the "Main Menu" screen.
 *
 * #include "UIMainMenuLayout.h"
 *
 * The class that represents the "Main Menu" screen that you see after pressing confirm at the title screen.
 * There are three options on the Main Menu: "New Game", "Set Password", and "Quit"
 *
 * @see UITitleScreenLayout, UIBattleScreenLayout, UISetPasswordLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */

#ifndef UIMainMenuLayout_h
#define UIMainMenuLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIMainMenuLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIMainMenuLayout(void);

    /**
     * Destructor.
	 */
    ~UIMainMenuLayout(void);

// OPERATORS
// OPERATIONS
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

#endif  // _UIMainMenuLayout_h_
