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
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs
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
#include <GameEngine/Level.h>
#include <GameEngine/GameEngine.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef vector<Character*> CharacterPtrVec;
typedef CharacterPtrVec::iterator CharacterPtrItr;


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
	virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     * Overriding OnLoad function to allow for additional communication.
	 */
	virtual void OnLoad( void );

// ACCESS (writing)

    /**
     * Change event handler to Menu
     */
    //void switchToMenu(void);

    /**
     * Change event handler to Grid
     */
    //void switchToGrid(void);


// INQUIRY (reading)

    /**
     * allows access to currently loaded level (for elements UIGrid and UIMenu)
     */
    Level* GetLevel(void);

protected:
// PROTECTED VARIABLES
    UIMenu* mMenu;
    UIGrid* mGrid;
    //int mGameState;
    //Level* mLevel;
    //GameEngine *mGameEngine;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIBattleScreenLayout_h_
