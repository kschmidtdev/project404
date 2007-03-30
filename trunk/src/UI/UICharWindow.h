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
 * Andrew Osborne, March 15 2007, Added Level and Class to List of info
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 29 2007 | Added new attributes (armor, weapon, and agility)
 */

#ifndef UICharWindow_h
#define UICharWindow_h

// SYSTEM INCLUDES
//
#include <UI/UIText.h>
#include <UI/UIImage.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class Character;

class UICharWindow : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UICharWindow(void);

    /**
     * Destructor.
	 */
    ~UICharWindow(void);

// OPERATORS

// OPERATIONS

     /**
     * Override RenderSelf operation
     */
    virtual void RenderSelf(SDL_Surface* destination);

    /**
     * Update Information
     */
    void Update() { SetCharacter(mCurCharacter); }

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
    UIText mCharName;  // Includes class
    UIText mLevel;
    UIText mHPTitle;
    UIText mHP;
    UIText mHPSlash;
    UIText mHPMax;
    //UIText mMPTitle;
    //UIText mMP;
    //UIText mMPSlash;
    //UIText mMPMax;
    UIText mStrText;
    UIText mCharStr;
    UIText mDefText;
    UIText mCharDef;
    UIText mAglText;
    UIText mCharAgl;

    UIText mArmor;
    UIText mEquip;
    UIText mWeapon;

    // Image display coordinates (relative to the CharWindow base)
    Point mNameStart;

    Point mLevelStart;

    Point mHPStart;
    int mValOffset;
    int mSlashOffset;
    int mMaxOffset;
    Point mMPStart;

    Point mStrStart;
    int mStrOffset;
    Point mDefStart;
    int mDefOffset;
    Point mAglStart;
    int mAglOffset;

    Point mLineOffset;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UICharWindow_h_
