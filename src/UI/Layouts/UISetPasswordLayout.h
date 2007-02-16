/**
 * A one line description of the class.
 *
 * #include "UISetPasswordLayout.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007, Initial Creation
 */

#ifndef UISetPasswordLayout_h
#define UISetPasswordLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>
#include <UIText.h>

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
    string mOldStarString;
    string mNewStarString;
    string mConfirmStarString;
    UIText *mOldPwdUIText;
    UIText *mNewPwdUIText;
    UIText *mConfirmPwdUIText;
    string mOldPwd;
    string mNewPwd;
    string mConfirmPwd;

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
