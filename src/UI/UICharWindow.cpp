/**
 * File: UICharWindow.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 9 2007 | Initial Creation
 * Andrew Osborne, March 10 2007 | Completed Implementation
 * Andrew Osborne, March 14 2007 | Made it so by default, mElementImage has something stored in it
 *                                      and by default, the blank image is displayed
 * Andrew Osborne, March 15 2007 | Added Level and Class to information Listed.
 */
#include "UICharWindow.h"                                // class implemented
#include <sstream>



/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICharWindow::UICharWindow()
: mDefaultBlankImage( NULL ), mDefaultCharBackground( NULL ),
mCurCharacter( NULL ), mAttackTargetCharacter( NULL ),
mCharacterView( true ), mValOffset( 0 ), mSlashOffset( 0 ), mMaxOffset( 0 ),
mStrOffset( 0 ), mDefOffset( 0 )
{

    // Setup backgrounds
    mDefaultCharBackground = ResourceManager::GetInstance()->LoadTexture("CharWindowBackground.png");
    mDefaultBlankImage = ResourceManager::GetInstance()->LoadTexture("CharWindowBackground.png");

    // Text Position parameters
    int xStart = 20;
    int yNameStart = 20;
    int textSpacing = 4; // Seems to be some sort of 'additional'
    int defaultTextSize = 12;
    int nameGap = 20;

    mNameStart.Set(xStart, yNameStart);

    mLevelStart.Set(xStart, mNameStart.GetY() + defaultTextSize + textSpacing + nameGap);

    mHPStart.Set(xStart, mLevelStart.GetY() + defaultTextSize + textSpacing);
    mValOffset = 84;
    mSlashOffset = mValOffset + 30;
    mMaxOffset = mSlashOffset + 20;

    // Str/Def
    mStrStart.Set(xStart, mHPStart.GetY() + defaultTextSize + textSpacing);
    mStrOffset = 65;
    mDefStart.Set(xStart, mStrStart.GetY() + defaultTextSize + textSpacing);
    mDefOffset = mStrOffset;

    std::ostringstream oss;
    string str;

    // Initialize color parameters
    int HPRed = 0;
    int HPGreen = 0;
    int HPBlue = 0;

    // Initialize Static Text (and set colour/size parameters)

    mCharName.ChangeText( "Name", defaultTextSize, HPRed, HPGreen, HPBlue );

    // HP/MP
    oss << 999;
    str = oss.str();

    mLevel.ChangeText("Level 0", defaultTextSize, HPRed, HPGreen, HPBlue );

    mHPTitle.ChangeText( "Health Point : ", defaultTextSize, HPRed, HPGreen, HPBlue );
    mHP.ChangeText( str, defaultTextSize, HPRed, HPGreen, HPBlue );
    mHPSlash.ChangeText( "/", defaultTextSize, HPRed, HPGreen, HPBlue );
    mHPMax.ChangeText( str, defaultTextSize, HPRed, HPGreen, HPBlue );

    mStrText.ChangeText("Strength : ", defaultTextSize, HPRed, HPGreen, HPBlue );
    mCharStr.ChangeText("99", defaultTextSize, HPRed, HPGreen, HPBlue );
    mDefText.ChangeText("Defence :  ", defaultTextSize,HPRed, HPGreen, HPBlue );
    mCharDef.ChangeText("99", defaultTextSize, HPRed, HPGreen, HPBlue );

    //mPos.Set(440, 5);
    SetPos(mPos);

    ClearCharacter();

}// UICharWindow





UICharWindow::~UICharWindow()
{


}// ~UICharWindow


//============================= OPERATORS ====================================




void UICharWindow::RenderSelf(SDL_Surface* destination)
{

    if (mVisible)
    {
        if (mCharacterView)
        {
            UIElement::RenderSelf(destination);

            // Name
            mCharName.RenderSelf(destination);

            // Level
            mLevel.RenderSelf(destination);

            // HP/MP
            mHPTitle.RenderSelf(destination);
            mHP.RenderSelf(destination);
            mHPSlash.RenderSelf(destination);
            mHPMax.RenderSelf(destination);

            // Str/Def
            mStrText.RenderSelf(destination);
            mCharStr.RenderSelf(destination);
            mDefText.RenderSelf(destination);
            mCharDef.RenderSelf(destination);
        }
        else
        {
            UIElement::RenderSelf(destination);
        }

    }

}

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================

void UICharWindow::SetCharacter(Character *c)
{


    mCurCharacter = c;

    if (mCurCharacter!=NULL)
    {

        std::ostringstream oss;
        string str;

        // Character's name
        mCharName.ChangeText( mCurCharacter->GetName() + "  (" + mCurCharacter->GetClassName() + ")" );

        // Character's Level
        string lvlText;
        oss << mCurCharacter->GetLevel();
        lvlText = "Level: " + oss.str() + ",   ";
        oss.str("");
        oss << mCurCharacter->GetExp();
        lvlText += "Exp: " + oss.str();
        mLevel.ChangeText( lvlText );
        oss.str("");

        // Character's HP
        oss << mCurCharacter->GetHP();
        mHP.ChangeText( oss.str() );
        oss.str("");

        // Character's HP max
        oss << mCurCharacter->GetMaxHP();
        mHPMax.ChangeText( oss.str() );
        oss.str("");

        // Character's Strength
        oss << mCurCharacter->GetAttr(Character::POW);
        mCharStr.ChangeText( oss.str() );
        oss.str("");

        // Character's Defense
        oss << mCurCharacter->GetAttr(Character::DEF);
        mCharDef.ChangeText( oss.str() );
        oss.str("");

        mCharacterView = true;

        // Element Image
        mElementImage = mDefaultCharBackground;

    }
    else
    {
        mCharName.ChangeText("NULL");
        mCharacterView = true;
    }

}


void UICharWindow::ClearCharacter(void)
{
    mCurCharacter = NULL;
    mCharacterView = false;
    mElementImage = mDefaultBlankImage;
}

void UICharWindow::SetPos( const Point & nPos )
{

    mPos = nPos;

    // Name
    mCharName.SetPos(mPos + mNameStart );

    // Level
    mLevel.SetPos(mPos + mLevelStart );

    // HP/MP
    mHPTitle.SetPos( mPos + mHPStart );
    mHP.SetPos( mPos + mHPStart + Point(mValOffset,0) );
    mHPSlash.SetPos( mPos + mHPStart + Point(mSlashOffset,0) );
    mHPMax.SetPos( mPos + mHPStart + Point(mMaxOffset,0) );
    //mMPTitle.SetPos( mPos + mMPStart );
    //mMP.SetPos( mPos + mMPStart + Point(mValOffset,0) );
    //mMPSlash.SetPos( mPos + mMPStart + Point(mSlashOffset,0) );
    //mMPMax.SetPos( mPos + mMPStart + Point(mMaxOffset,0) );

    // Str/Def
    mStrText.SetPos( mPos + mStrStart );
    mCharStr.SetPos( mPos + mStrStart + Point(mStrOffset,0) );
    mDefText.SetPos( mPos + mDefStart );
    mCharDef.SetPos( mPos + mDefStart + Point(mDefOffset,0) );

}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
