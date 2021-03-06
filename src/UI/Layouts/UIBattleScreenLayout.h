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
 * Karl Schmidt,   February 14 2007 | Updated function capitalization, block style, typedefs
 * Mike Malyuk,    February 15 2007 | Added function to get grid
 * Karl Schmidt, February 15 2007   | Added Initialize and OnClose override
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UIBattleScreenLayout_h
#define UIBattleScreenLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>
#include <UI/UIMenu.h>
#include <UI/UIGrid.h>
#include <GameEngine/Level.h>
#include <GameEngine/GameEngine.h>

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

    /**
     * Creates UIGrid and other elements for this layout
	 */
    void Initialize();

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

    /**
     * Overriding OnLoad function to allow for additional communication.
	 */
	virtual void OnClose( void );

// ACCESS (writing)

// INQUIRY (reading)

    /**
     * allows access to currently loaded level (for elements UIGrid and UIMenu)
     */
    Level* GetLevel(void);

    /**
     * allows access to currently loaded grid
     */
    UIGrid* GetGrid(void);

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
