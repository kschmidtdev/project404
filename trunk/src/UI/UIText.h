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
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
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
    UIText( const string & text, const int size, const int r, const int g, const int b);

    /**
     * Partial constructor.
	 */
    UIText( const string & text);

    /**
     * Destructor.
	 */
    virtual ~UIText(void);

// OPERATORS


// OPERATIONS

    /**
     * Method that changes text .
	 */
    void CenterText(UIElement* e);

// ACCESS (writing)

    /**
     * Method that changes text .
	 */
    void ChangeText(const string & newText);

    /**
     * New Text (with parameters)
     */
    void ChangeText(const string & newText, const int s, const int r, const int g, const int b);

    /**
     * Change Colour.
	 */
    void SetColour( const int r, const int g, const int b);

    /**
     * Change Size.
	 */
    void SetSize( const int s);



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
