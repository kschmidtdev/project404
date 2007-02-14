/**
 * A one line description of the class.
 *
 * #include "UIText.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
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
     * Change Colour.
	 */
    void SetColour(int r, int g, int b);

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
