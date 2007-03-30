/**
 * UILayout sub-class for the main battle screen
 *
 * #include "UITitleScreenLayout.h"
 *
 * UILayout sub-class for the main battle screen
 *
 * @see UILayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 10 2007 | Documentation
 * Andrew Osborne, February 14 2007 | Added ProcessEvent handling
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Karl Schmidt, March 29 2007      | Added title image fading
 */

#ifndef UITitleScreenLayout_h
#define UITitleScreenLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIImage;

class UITitleScreenLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UITitleScreenLayout(void);

    /**
     * Destructor.
	 */
    ~UITitleScreenLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Method to Process input from user
     *
     * @param inputManager event
     *
     */
    virtual void UITitleScreenLayout::ProcessEvent( const InputManager::INPUTKEYS evt );

    void Update();

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:

    enum FADING_STATE
    {
        TEAMTITLE_IN = 0,
        TEAMTITLE_WAIT,
        TEAMTITLE_OUT,
        CASTLETITLE_IN,
        CASTLETITLE_DONE
    };

    UIImage* mTeamTitle;
    UIImage* mCastleTitle;

    FADING_STATE mFadeState;
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UITitleScreenLayout_h_
