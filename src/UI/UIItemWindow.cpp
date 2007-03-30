/**
 * File: UIItemWindow.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 * Karl Schmidt, March 29 2007      | Added correct superclass constructor calling
 */
#include "UIItemWindow.h"                                // class implemented
#include <GameEngine/Item.h>
#include <ResourceManager/ResourceManager.h>
#include <sstream>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIItemWindow::UIItemWindow()
: UIElement(), mDisplayCost( false ), mDisplayItem( false ),
mFontSize( 16 ), mFontRed( 0 ), mFontGreen( 0 ), mFontBlue( 0 )
{

    mElementImage = ResourceManager::GetInstance()->LoadTexture("charWindowBackground.png");

    mType.ChangeText("Name: ", mFontSize, mFontRed, mFontGreen, mFontBlue );
    mNameStatic.ChangeText("Name: ", mFontSize, mFontRed, mFontGreen, mFontBlue );
    mName.ChangeText(" ", mFontSize, mFontRed, mFontGreen, mFontBlue );
    mAttrStatic.ChangeText("Attr: ", mFontSize, mFontRed, mFontGreen, mFontBlue );
    mAttr.ChangeText(" ", mFontSize, mFontRed, mFontGreen, mFontBlue );
    mCostStatic.ChangeText("Cost: ", mFontSize, mFontRed, mFontGreen, mFontBlue );
    mCost.ChangeText(" ", mFontSize, mFontRed, mFontGreen, mFontBlue );

    mStart.Set(20, 20);
    mLineOffset.Set(0, mFontSize + 5);
    mNumOffset.Set( 60, 0 );

    SetPos(mPos);

}// UIItemWindow


UIItemWindow::~UIItemWindow()
{
}// ~UIItemWindow


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================


void UIItemWindow::RenderSelf(SDL_Surface* destination)
{
    UIElement::RenderSelf(destination);

    mNameStatic.RenderSelf(destination);
    mAttrStatic.RenderSelf(destination);
    if (mDisplayCost)
        mCostStatic.RenderSelf(destination);


    if (mDisplayItem)
    {
        mType.RenderSelf(destination);
        mName.RenderSelf(destination);
        mAttr.RenderSelf(destination);
        if (mDisplayCost)
            mCost.RenderSelf(destination);
    }

}


//============================= ACCESS     ===================================

void UIItemWindow::SetPos( const Point & nPos )
{
    UIElement::SetPos(nPos);

    mType.SetPos( mPos + mStart );
    mNameStatic.SetPos( mType.GetPos() + mLineOffset );
    mName.SetPos( mNameStatic.GetPos() + mNumOffset );
    mAttrStatic.SetPos( mNameStatic.GetPos() + mLineOffset );
    mAttr.SetPos( mAttrStatic.GetPos() + mNumOffset );
    mCostStatic.SetPos( mAttrStatic.GetPos() + mLineOffset );
    mCost.SetPos( mCostStatic.GetPos() + mNumOffset );

}

void UIItemWindow::SetItem(Item* newItem)
{
    if (newItem)
    {

        if (newItem->GetType()==Item::ARMOR)
        {
            mType.ChangeText("Armor");
        }
        else
        {
            mType.ChangeText("Weapon");
        }

        mName.ChangeText( newItem->GetName() );

        std::ostringstream oss;
        oss << newItem->GetAttr();
        mAttr.ChangeText( oss.str() );

        oss.str("");
        oss << newItem->GetCost();
        mCost.ChangeText( oss.str() );

        mDisplayItem = true;

    }

}


void UIItemWindow::ClearItem(void)
{
    mDisplayItem = false;
}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
