/**
 * The Layout class that represents the "Set Password" Screen
 *
 * #include "UISetPasswordLayout.h"
 *
 * The Layout class that represents the "Set Password" Screen, which allows you to set a new password
 * This screen is accessible from the Main Menu.
 *
 * @see UIMainMenuLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */

#ifndef UISetPasswordLayout_h
#define UISetPasswordLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>
#include <UI/UIText.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UISetPasswordLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UISetPasswordLayout(void);

    /**
     * Destructor.
	 */
    ~UISetPasswordLayout(void);

// OPERATORS


// OPERATIONS

    /**
     * Method to Process input from user
     *
     * @param inputManager event
     *
     */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );


// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    int mPasswordEntryState;
    std::string mOldStarString;
    std::string mNewStarString;
    std::string mConfirmStarString;
    UIText *mOldPwdUIText;
    UIText *mNewPwdUIText;
    UIText *mConfirmPwdUIText;
    std::string mOldPwd;
    std::string mNewPwd;
    std::string mConfirmPwd;

// PROTECTED METHODS
    void AddStar(void);

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UISetPasswordLayout_h_
