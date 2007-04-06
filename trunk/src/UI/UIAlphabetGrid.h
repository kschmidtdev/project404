/**
 * Element that represents text entry mechanism.
 *
 * #include "UIAlphabetGrid.h"
 *
 * Element that represents text entry mechanism.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 20 2007, Initial Creation
 * Andrew Osborne, March 21 2007, Added Process Event, incorporated CenterText
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added start offset
 * Andrew Osborne, March 24 2007 | converted from EventListener to UIEventListener
 * Andrew Osborne, March 24 2007 | Finally added ability to jump to menu
 * Mike Malyuk,    March 31 2007 | Removed unused methods and variables related to menu and other.
 * Andrew Osborne, April 5 2007 | Added mHelp text (for feedback), respective setter, and ability to clear text
 */

#ifndef UIAlphabetGrid_h
#define UIAlphabetGrid_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <UI/UIImage.h>
#include <UI/UIText.h>
#include <UIEventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UILayout;

typedef std::vector<UIText*> UITextVec;
typedef UITextVec::iterator UITextItr;

class UIAlphabetGrid : public UIElement, public UIEventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIAlphabetGrid(void);

    /**
     * Destructor.
	 */
    ~UIAlphabetGrid(void);

// OPERATORS
// OPERATIONS

    /**
     * Override RenderSelf operation
     */
    virtual void RenderSelf(SDL_Surface* destination);

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     *  Change text to uppercase input
     */
    //void ToUpperCase(void);

    /**
     * Find mLetters index value
     */
    //int GetIndex( Point p );

    /**
     * (Visually) Enables Element
     */
    virtual void Enable(void);

    /**
     * (Visually) Disables Element
     */
    virtual void Disable(void);

// ACCESS (writing)

    /**
     * Override Set Position
     */
    virtual void SetPos( const Point & nPos );

    /**
     * clears text
     */
    void ClearString();

    /**
     * Set message text
     */
    void SetMessageText(UIText* text) { mHelp = text; }


// INQUIRY (reading)

    /**
     * Returns currently constructed string
     */
    const std::string & GetString(void) { return mResult; }

protected:
// PROTECTED VARIABLES

    // Letter Grid
    std::string mAlphabet;
    UITextVec mLetters;

    // String result
    UIText mUIResult;
    std::string mResult;

    // Cursor
    UIImage* mCursor;
    Point mCursorPos;

    // Font format
    int mFontSize;
    int mFontRed;
    int mFontGreen;
    int mFontBlue;

    // Display Format
    Point mGrid; // max - num of rows and columns
    Point mOffset; // Offset for each row/column
    Point mGridStart;

    // External text
    UIText* mHelp;

// PROTECTED FUNCTIONS

    /**
     *  Updates Cursor position
     */
    void UpdateCursor(void);

    /**
     *  Adds current character to main string (mResult)
     */
    void AddChar(void);

    /**
     *  Removes one character from main string (mResult)
     */
    void RemoveChar(void);

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIAlphabetGrid_h_
