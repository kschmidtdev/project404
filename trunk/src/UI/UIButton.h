/**
 * The base class for a button element on screen
 *
 * #include "UIButton.h"
 *
 * The only addition feature of a button element will be a constructor that allows for the passed string to be seen
 * on the button
 *
 * @see UIMenu
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, February 14 2007   | Updated function capitalization, block style, typedefs
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UIButton_h
#define UIButton_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIText.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class FuncObj;


class UIButton : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIButton(void);

    /**
     * Default constructor.
	 */
	UIButton(const std::string & text);

    /**
     * Destructor.
	 */
    ~UIButton(void);

// OPERATORS
    /**
     * Override Renderself to allow for text to be written as well.
	 */
    virtual void RenderSelf(SDL_Surface* destination);


// OPERATIONS
// ACCESS (writing)

    /**
     * Set position of button - automatically moves and centers text with it.
	 */
    virtual void SetPos( const Point & nPos );

    /**
     * Set Ghost
     */
    void SetGhost(bool b);

// INQUIRY (reading)

    /**
     * Get Ghost
     */
    bool GetGhost(void) { return mGhost; }

protected:
// PROTECTED VARIABLES
    UIText mText;
    FuncObj* mOperation;
    bool mGhost;

    // Font information
    static int mActiveRed;
    static int mActiveGreen;
    static int mActiveBlue;
    static int mGhostRed;
    static int mGhostGreen;
    static int mGhostBlue;
    static int mTextSize;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIButton_h_
