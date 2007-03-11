/**
 * The window that displays a character's stats
 *
 * #include "UICharWindow.h"
 *
 * The window that displays a character's stats.
 *
 * @see UIBattleLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 9 2007, Initial Creation
 */

#ifndef UICharWindow_h
#define UICharWindow_h

// SYSTEM INCLUDES
//
#include <UIElement.h>
#include <UIText.h>
#include <UIImage.h>
#include <GameEngine/Character.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UICharWindow : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UICharWindow(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UICharWindow(const UICharWindow& from);

    /**
     * Destructor.
	 */
    ~UICharWindow(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UICharWindow&                     operator=(UICharWindow& from);

// OPERATIONS

     /**
     * Override RenderSelf operation
     */
    virtual void RenderSelf(SDL_Surface* destination);


// ACCESS (writing)

    /**
     * Sets display to certain chararcter
     */
    void SetCharacter(Character *c);

    /**
     * Clears display to certain chararcter
     */
    void ClearCharacter(void);

    /**
     * Override Set Position
     */
    virtual void SetPos( const Point & nPos );

// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    SDL_Surface* mDefaultBlankImage;
    SDL_Surface* mDefaultCharBackground;
    Character* mCurCharacter;
    Character* mAttackTargetCharacter;
    bool mCharacterView;

    // Image display elements (UIElements)
    UIImage mCharImage;
    UIText mCharName;
    UIText mHPTitle;
    UIText mHP;
    UIText mHPSlash;
    UIText mHPMax;
    UIText mMPTitle;
    UIText mMP;
    UIText mMPSlash;
    UIText mMPMax;
    UIText mStrText;
    UIText mCharStr;
    UIText mDefText;
    UIText mCharDef;

    // Image display coordinates (relative to the CharWindow base)
    Point mNameStart;

    Point mHPStart;
    int mValOffset;
    int mSlashOffset;
    int mMaxOffset;
    Point mMPStart;

    Point mStrStart;
    int mStrOffset;
    Point mDefStart;
    int mDefOffset;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UICharWindow_h_
