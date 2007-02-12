/**
 * UILayout class for main battle screen
 *
 * #include "UIBattleScreenLayout.h"
 *
 * The screen we need to run the game
 *
 * @see GameEngine, UILayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Crude Creation
 */

#ifndef UIBattleScreenLayout_h
#define UIBattleScreenLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>
#include <UIMenu.h>
#include <UIGrid.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIBattleScreenLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIBattleScreenLayout(void);

    /**
     * Destructor.
	 */
    ~UIBattleScreenLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Overrides the ProcessEvent so that it can control the cursor.
	 */
	//virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

// ACCESS (writing)

    /**
     * Change event handler to Menu
     */
    void switchToMenu(void);

    /**
     * Change event handler to Grid
     */
    void switchToGrid(void);


// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIMenu* mMenu;
    UIGrid* mGrid;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIBattleScreenLayout_h_
