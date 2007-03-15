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
    mDefaultBlankImage = ResourceManager::GetInstance()->LoadTexture("CharWindowBlank.png");

    // Text Position parameters
    int xStart = 10;
    int yNameStart = 7;
    int textSpacing = 0; // Seems to be some sort of 'additional'
    int defaultTextSize = 24;
    int nameGap = 20;

    mNameStart.Set(xStart, yNameStart);

    mHPStart.Set(xStart, mNameStart.GetY() + defaultTextSize + textSpacing + nameGap);
    mValOffset = 47;
    mSlashOffset = mValOffset + 50;
    mMaxOffset = mSlashOffset + 17;
    //mMPStart.Set(xStart, mHPStart.GetY() + defaultTextSize + textSpacing + nameGap);

    // Str/Def
    mStrStart.Set(xStart, mHPStart.GetY() + defaultTextSize + textSpacing + 5);
    mStrOffset = 55;
    mDefStart.Set(xStart + mStrOffset + 40, mStrStart.GetY() );
    mDefOffset = mStrOffset;

    std::ostringstream oss;
    string str;

    // Initialize color parameters
    int HPRed = 250;
    int HPGreen = 250;
    int HPBlue = 0;

    //int MPRed = 0;
    //int MPGreen = 0;
    //int MPBlue = 255;

    // Initialize Static Text (and set colour/size parameters)

    mCharName.ChangeText( "NAME", 24, HPRed, HPGreen, HPBlue );

    // HP/MP
    oss << 999;
    str = oss.str();

    mHPTitle.ChangeText( "HP: ", defaultTextSize, HPRed, HPGreen, HPBlue );
    mHP.ChangeText( str, defaultTextSize, HPRed, HPGreen, HPBlue );
    mHPSlash.ChangeText( "/", defaultTextSize, HPRed, HPGreen, HPBlue );
    mHPMax.ChangeText( str, defaultTextSize, HPRed, HPGreen, HPBlue );

    /*mMPTitle.ChangeText( "MP: ", defaultTextSize, MPRed, MPGreen, MPBlue );
    mMP.ChangeText( str, defaultTextSize, MPRed, MPGreen, MPBlue );
    mMPSlash.ChangeText( "/", defaultTextSize, MPRed, MPGreen, MPBlue );
    mMPMax.ChangeText( str, defaultTextSize, MPRed, MPGreen, MPBlue );*/


    mStrText.ChangeText("STR ", defaultTextSize, HPRed, HPGreen, HPBlue );
    mCharStr.ChangeText("99", defaultTextSize, HPRed, HPGreen, HPBlue );
    mDefText.ChangeText("DEF ", defaultTextSize,HPRed, HPGreen, HPBlue );
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

    //UIElement::RenderSelf(destination);

    if (mVisible)
    {
        if (mCharacterView)
        {
            //mElementImage = mDefaultCharBackground;
            UIElement::RenderSelf(destination);

            // Name
            mCharName.RenderSelf(destination);

            // HP/MP
            mHPTitle.RenderSelf(destination);
            mHP.RenderSelf(destination);
            mHPSlash.RenderSelf(destination);
            mHPMax.RenderSelf(destination);

            //mMPTitle.RenderSelf(destination);
            //mMP.RenderSelf(destination);
            //mMPSlash.RenderSelf(destination);
            //mMPMax.RenderSelf(destination);

            // Str/Def
            mStrText.RenderSelf(destination);
            mCharStr.RenderSelf(destination);
            mDefText.RenderSelf(destination);
            mCharDef.RenderSelf(destination);
        }
        else
        {
            //mElementImage = mDefaultBlankImage;
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
        mCharName.ChangeText( mCurCharacter->GetName() );

        // Character's HP
        oss << mCurCharacter->GetHP();
        mHP.ChangeText( oss.str() );
        oss.str("");

        // Character's HP max
        oss << mCurCharacter->GetMaxHP();
        mHPMax.ChangeText( oss.str() );
        oss.str("");

        // Character's MP
        //oss << mCurCharacter->GetMP();
        //mMP.ChangeText( oss.str() );

        // Character's MP max
        //oss << mCurCharacter->GetMaxMP();
        //mMPMax.ChangeText( oss.str() );

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

    // HP/MP
    mHPTitle.SetPos( mPos + mHPStart );
    mHP.SetPos( mPos + mHPStart + Point(mValOffset,0) );
    mHPSlash.SetPos( mPos + mHPStart + Point(mSlashOffset,0) );
    mHPMax.SetPos( mPos + mHPStart + Point(mMaxOffset,0) );
    mMPTitle.SetPos( mPos + mMPStart );
    mMP.SetPos( mPos + mMPStart + Point(mValOffset,0) );
    mMPSlash.SetPos( mPos + mMPStart + Point(mSlashOffset,0) );
    mMPMax.SetPos( mPos + mMPStart + Point(mMaxOffset,0) );

    // Str/Def
    mStrText.SetPos( mPos + mStrStart );
    mCharStr.SetPos( mPos + mStrStart + Point(mStrOffset,0) );
    mDefText.SetPos( mPos + mDefStart );
    mCharDef.SetPos( mPos + mDefStart + Point(mDefOffset,0) );

}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
