/**
 * UIElement that represents a list of objects/elements.
 *
 * #include "UIList.h"
 *
 * UIElement that represents a list of objects/elements.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 */

#ifndef UIList_h
#define UIList_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <UICursor.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIList : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIList(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIList(const UIList& from);

    /**
     * Destructor.
	 */
    ~UIList(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIList&                     operator=(UIList& from);

// OPERATIONS

    /**
     * Method renders menu on screen
	 *
	 * @param the destination (SDL_Surface) where the list will go.
	 *
	 */
    virtual void RenderSelf(SDL_Surface *destination);

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

// ACCESS (writing)

    /**
     * Override SetPos
    */
    virtual void SetPos( const Point & nPos);

    /**
     * Add multiple lines
     */
    void AddLines(StringVec* list);

    /**
     *  Add single line
     *
     *@return returns integer index
     */
    int AddLine(string s);

    /**
     * Set Confirm Function
     */
    void SetConfirmFunc(FuncObj* f);

    /**
     * Set Cancel Function
     */
    void SetCancelFunc(FuncObj* f);

    /**
     * Enable Menu (make cursor visible)
     */
    void Enable(void);

    /**
     * Disable Menu (make cursor invisible)
     */
    void Disable(void);


// INQUIRY (reading)

    /**
     * Returns currently highlighted string (highlighted with cursor)
     */
    string GetCurString(void);

    /**
     * Returns currently highlighted index (highlighted with cursor)
     */
    int GetCurIndex(void);

protected:
// PROTECTED VARIABLES

    // Data
    vector<string> mStringList;
    vector<UIText> mUIList;
    Point mDataStart;
    Point mDataOffset;

    // Title
    UIText mTitle;
    Point mTitleStart; // Position relative to List

    // Cursor
    int mCurIndex;
    int mMaxIndex;
    UICursor* mCursor;

    // Functionality
    FuncObj* mConfirmFunc;
    FuncObj* mCancelFunc;

    // Text formating
    static int mFontSize = 16;

    static int mFontRed = 0;
    static int mFontGreen = 0;
    static int mFontBlue = 0;

    static int mFontHighlightRed = 255;
    static int mFontHighlightGreen = 255;
    static int mFontHighlightBlue = 255;





private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIList_h_
