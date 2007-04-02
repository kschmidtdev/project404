/**
 * File: UITutorialLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation (stub)
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Proper Implementation of Tutorial Layout
 * Karl Schmidt, April 2 2007    | Added support for final tutorial, plus resetting tutorial on re-entry
 */
#include "UITutorialLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
//#include <UI/UIText.h>
#include <UI/UIImage.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITutorialLayout::UITutorialLayout()
: mMinLayoutNum( 1 ), mMaxLayoutNum( 13 ), mCurLayoutNum( 1 ),
mBack( NULL )
{
    // Screen Name
    mName = "Tutorial";

    // Declaring image file prefix
    mLayoutFileNamePrefix = "tutorial_";
    mLayoutFileNameSuffix = ".png";

    // Calling first file
    std::ostringstream oss;
    oss << mCurLayoutNum;
    mBack = new UIImage( mLayoutFileNamePrefix + oss.str() + mLayoutFileNameSuffix );
    mElements.push_back(mBack);



}// UITutorialLayout


UITutorialLayout::~UITutorialLayout()
{
}// ~UITutorialLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UITutorialLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    bool changed = false;

    switch (evt)
    {
        case InputManager::CONFIRM:
        case InputManager::RIGHT:
            if (mCurLayoutNum<mMaxLayoutNum)
            {
                mCurLayoutNum++;
                changed = true;
            }
            else if (mCurLayoutNum>=mMaxLayoutNum)
            {
                // End of tutorial
                UIManager::GetInstance()->PopLayout();
                UIManager::GetInstance()->PushLayout("OverMap");
            }
            break;
        case InputManager::CANCEL:
        case InputManager::LEFT:
            if (mCurLayoutNum>mMinLayoutNum)
            {
                mCurLayoutNum--;
                changed = true;
            }
            else if (mCurLayoutNum<=mMinLayoutNum)
            {
                //UIManager::GetInstance()->PopLayout();
            }
            break;
        default:
            break;
    }

    if (changed)
    {
        std::ostringstream oss;
        oss << mCurLayoutNum;
        mBack->SetImage( mLayoutFileNamePrefix + oss.str() + mLayoutFileNameSuffix );
    }

}

void UITutorialLayout::OnLoad()
{
    UILayout::OnLoad();

    mCurLayoutNum = 1;
    // Calling first file
    std::ostringstream oss;
    oss << mCurLayoutNum;
    mBack->SetImage( mLayoutFileNamePrefix + oss.str() + mLayoutFileNameSuffix );
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
