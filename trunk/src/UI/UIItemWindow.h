/**
 * A description window for items.
 *
 * #include "UIItemWindow.h"
 *
 *  A description window for items.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 29 2007, Initial Creation
 */

#ifndef UIItemWindow_h
#define UIItemWindow_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
//#include <UI/UIImage.h>
#include <UI/UIText.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class Item;

class UIItemWindow : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIItemWindow(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIItemWindow(const UIItemWindow& from);

    /**
     * Destructor.
	 */
    ~UIItemWindow(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIItemWindow&                     operator=(UIItemWindow& from);

// OPERATIONS

    /**
     * Override RenderSelf operation
     */
    virtual void RenderSelf(SDL_Surface* destination);


// ACCESS (writing)

    /**
     * Override Set Position
     */
    virtual void SetPos( const Point & nPos );

    /**
     * Set Item
     */
    void SetItem(Item* newItem);

    /**
     * Clears Item Display
     */
    void ClearItem(void);

    /**
     * Specify to display cost or not
     */
    void SetDisplayCost(bool displayCost) { mDisplayCost = displayCost; }


// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    UIText mType;
    UIText mNameStatic;
    UIText mName;
    UIText mAttrStatic; // contains static text "Attr: "
    UIText mAttr;
    UIText mCostStatic; // Cost:
    UIText mCost;

    // Display format
    bool mDisplayCost;
    bool mDisplayItem;

    // Font format
    int mFontSize;
    int mFontRed;
    int mFontGreen;
    int mFontBlue;

    // Positional stuff
    Point mStart;
    Point mLineOffset;
    Point mNumOffset;
    //Point mNameStaticStart;
    //Point mName;
    //Point mAttrStatic; // contains static text "Attr: "
    //Point mAttr;
    //Point mCostStatic; // Cost:
    //Point mCost;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIItemWindow_h_
