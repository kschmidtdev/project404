/**
 * File: UICharWindow.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 9 2007  | Initial Creation
 * Andrew Osborne, March 10 2007 | Completed Implementation
 * Andrew Osborne, March 14 2007 | Made it so by default, mElementImage has something stored in it
 *                                      and by default, the blank image is displayed
 * Andrew Osborne, March 15 2007 | Added Level and Class to information Listed.
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Karl Schmidt, March 23 2007   | Got rid of more using namespace std; usage
 * Andrew Osborne, March 29 2007 | Fixed some spelling mistakes and added new attributes (armor, weapon, and agility)
 * Karl Schmidt, March 29 2007   | Added correct superclass constructor calling, fixed crashs when characters aren't
 								   equipped with anything
 */
#include "UICharWindow.h"                                // class implemented

#include <util.h>

#include <sstream>

#include <ResourceManager/ResourceManager.h>
#include <GameEngine/Character.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICharWindow::UICharWindow()
: UIElement(), mDefaultBlankImage( NULL ), mDefaultCharBackground( NULL ),
mCurCharacter( NULL ), mAttackTargetCharacter( NULL ),
mCharacterView( true ), mValOffset( 0 ), mSlashOffset( 0 ), mMaxOffset( 0 ),
mStrOffset( 0 ), mDefOffset( 0 )
{

    // Setup backgrounds
    mDefaultCharBackground = ResourceManager::GetInstance()->LoadTexture("CharWindowBackground.png");
    mDefaultBlankImage = ResourceManager::GetInstance()->LoadTexture("CharWindowBackground.png");

    // Text Position parameters
    int xStart = 20;
    int yNameStart = 15;
    int textSpacing = 4; // Seems to be some sort of 'additional'
    int defaultTextSize = 12;
    int nameGap = 2;

    mNameStart.Set(xStart, yNameStart);

    mLevelStart.Set(xStart, mNameStart.GetY() + defaultTextSize + textSpacing + nameGap);

    mHPStart.Set(xStart, mLevelStart.GetY() + defaultTextSize + textSpacing);
    mValOffset = 88;
    mSlashOffset = mValOffset + 30;
    mMaxOffset = mSlashOffset + 20;

    // Str/Def
    mStrStart.Set(xStart, mHPStart.GetY() + defaultTextSize + textSpacing);
    mStrOffset = 35;
    mDefStart.Set(xStart, mStrStart.GetY() + defaultTextSize + textSpacing);
    mDefOffset = mStrOffset;
    mAglOffset = mDefOffset;

    // Line
    mLineOffset.Set(0, defaultTextSize + textSpacing);


    std::ostringstream oss;
    std::string str;

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

    mHPTitle.ChangeText( "Health Points : ", defaultTextSize, HPRed, HPGreen, HPBlue );
    mHP.ChangeText( str, defaultTextSize, HPRed, HPGreen, HPBlue );
    mHPSlash.ChangeText( "/", defaultTextSize, HPRed, HPGreen, HPBlue );
    mHPMax.ChangeText( str, defaultTextSize, HPRed, HPGreen, HPBlue );

    mStrText.ChangeText("STR : ", defaultTextSize, HPRed, HPGreen, HPBlue );
    mCharStr.ChangeText("99", defaultTextSize, HPRed, HPGreen, HPBlue );
    mDefText.ChangeText("DEF :  ", defaultTextSize,HPRed, HPGreen, HPBlue );
    mCharDef.ChangeText("99", defaultTextSize, HPRed, HPGreen, HPBlue );
    mAglText.ChangeText("AGI: ", defaultTextSize, HPRed, HPGreen, HPBlue );
    mCharAgl.ChangeText("99", defaultTextSize, HPRed, HPGreen, HPBlue );

    mEquip.ChangeText("Equipment", defaultTextSize, HPRed, HPGreen, HPBlue );
    mArmor.ChangeText("None", defaultTextSize, HPRed, HPGreen, HPBlue );
    mWeapon.ChangeText("None", defaultTextSize, HPRed, HPGreen, HPBlue );

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
            mAglText.RenderSelf(destination);
            mCharAgl.RenderSelf(destination);

            mEquip.RenderSelf(destination);
            mArmor.RenderSelf(destination);
            mWeapon.RenderSelf(destination);
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
        std::string str;

        // Character's name
        mCharName.ChangeText( mCurCharacter->GetName() + "  (" + mCurCharacter->GetCharacterClassName() + ")" );

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

        // Character's Agility
        oss << mCurCharacter->GetAttr(Character::AGI);
        mCharAgl.ChangeText( oss.str() );
        oss.str("");

        // Character's Equipment
        Item* tempItem = mCurCharacter->GetArmor();
        if( tempItem )
        {
            mArmor.ChangeText( tempItem->GetName() + " (" + toString( tempItem->GetAttr() ) + ")" );
        }

        tempItem = mCurCharacter->GetWeapon();
        if( tempItem )
        {
            mWeapon.ChangeText( tempItem->GetName() + " (" + toString( tempItem->GetAttr() ) + ")" );
        }

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
    mDefText.SetPos( mCharStr.GetPos() + Point(25, 0) );
    mCharDef.SetPos( mDefText.GetPos() + Point(mDefOffset,0) );
    mAglText.SetPos( mCharDef.GetPos() + Point(25, 0) );
    mCharAgl.SetPos( mAglText.GetPos() + Point(mAglOffset,0) );

    mEquip.SetPos( mStrText.GetPos() + mLineOffset + Point(0,5) );
    mArmor.SetPos( mEquip.GetPos() + mLineOffset );
    mWeapon.SetPos( mArmor.GetPos() + mLineOffset );

}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
