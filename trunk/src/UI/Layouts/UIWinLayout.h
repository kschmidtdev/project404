/**
 * A one line description of the class.
 *
 * #include "UIWinLayout.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007, Initial Creations
 */

#ifndef UIWinLayout_h
#define UIWinLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "UILayout.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIWinLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIWinLayout(void);



    /**
     * Destructor.
	 */
    ~UIWinLayout(void);

// OPERATORS

    /**
     * Method to Process input from user
     *
     * @param inputManager event
     *
     */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

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

#endif  // _UIWinLayout_h_
