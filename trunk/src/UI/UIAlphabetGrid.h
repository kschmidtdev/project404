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
 */

#ifndef UIAlphabetGrid_h
#define UIAlphabetGrid_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <UIImage.h>
#include <UIText.h>
#include <EventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIAlphabetGrid : public UIElement, public EventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIAlphabetGrid(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIAlphabetGrid(const UIAlphabetGrid& from);

    /**
     * Destructor.
	 */
    ~UIAlphabetGrid(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIAlphabetGrid&                     operator=(UIAlphabetGrid& from);

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

// ACCESS (writing)

    /**
     * Override Set Position
     */
    virtual void SetPos( const Point & nPos );


// INQUIRY (reading)

    /**
     * Returns currently constructed string
     */
    string GetString(void) { return mResult; }

protected:
// PROTECTED VARIABLES

    // Letter Grid
    string mAlphabet;
    string mCapitalAlphabet;
    vector<UIText*> mLetters;

    // String result
    UIText mUIResult;
    string mResult;



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
