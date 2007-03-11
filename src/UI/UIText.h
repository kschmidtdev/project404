/**
 * A class that represents lone text on the screen.
 *
 * #include "UIText.h"
 *
 * A class that represents lone text on the screen like the text seen on the "Congradulations screen"
 *
 * @see UIWinLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 14 2007 | Initial Creation
 * Andrew Osborne, March 9 2007 | Added new ChangeText command that allows you to change all parameters
 */

#ifndef UIText_h
#define UIText_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIText : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIText(void);

    /**
     * Full constructor.
	 */
    UIText( const string text, int size, int r, int g, int b);

    /**
     * Partial constructor.
	 */
    UIText( const string text);

    /**
     * Destructor.
	 */
    ~UIText(void);

// OPERATORS


// OPERATIONS
// ACCESS (writing)

    /**
     * Method that changes text .
	 */
    void ChangeText(const string newText);

    /**
     * New Text (with parameters)
     */
    void ChangeText(const string newText, int s, int r, int g, int b);

    /**
     * Change Colour.
	 */
    void SetColour(int r, int g, int b);

    /**
     * Change Size.
	 */
    void SetColour(int s);



// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    int mRed;
    int mGreen;
    int mBlue;
    int mSize;
    string mText;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIText_h_
