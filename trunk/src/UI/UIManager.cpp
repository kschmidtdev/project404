/**
 * File: UIManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10, 2007 | Initial creation and testing
 * Andrew Osborne, February 10, 2007 | Added some comments, deleted inputFunction
 * Andrew Osborne, February 11 2007 | Added GetInstance method
 * Andrew Osborne, February 11 2007 | Added Destructor, added 'm' prefix to members
 * Karl Schmidt, February 13 2007 | Added paranoia check to destructor
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Andrew Osborne, February 14 2007 | Refined/debugged ability to push/pop layouts
 * Karl Schmidt, February 15 2007 | Fixed a minor odd header include path
 * Andrew Osborne, February 15 2007 | Added PopAllLayouts
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Karl Schmidt, March 29 2007      | Added Update(), starting game at Title screen
 */

#include "UIManager.h"                                  // class implemented

#include <util.h>

#include <Logger.h>
#include <UI/Layouts/UIBattleScreenLayout.h>
#include <UI/Layouts/UITitleScreenLayout.h>
#include <UI/Layouts/UIMainMenuLayout.h>
#include <UI/Layouts/UIWinLayout.h>
#include <UI/Layouts/UILoseLayout.h>
#include <UI/Layouts/UIPasswordVerificationLayout.h>
#include <UI/Layouts/UISetPasswordLayout.h>
#include <UI/Layouts/UIOverMapLayout.h>
#include <UI/Layouts/UIPartyStatusLayout.h>
#include <UI/Layouts/UIProfileMenuLayout.h>
#include <UI/Layouts/UINewProfileLayout.h>
#include <UI/Layouts/UILoadProfileLayout.h>
#include <UI/Layouts/UITutorialMenuLayout.h>
#include <UI/Layouts/UITutorialLayout.h>
#include <UI/Layouts/UILoadGameLayout.h>
#include <UI/Layouts/UICreditsLayout.h>
#include <UI/Layouts/UIOptionsLayout.h>
#include <UI/Layouts/UISaveGameLayout.h>
#include <UI/Layouts/UIArmoryLayout.h>
#include <UI/Layouts/UIMarketLayout.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIManager* UIManager::_instance = 0;

UIManager* UIManager::GetInstance()
{
    if( !_instance )
    {
        _instance = new UIManager();
    }
    return _instance;
}


 UIManager::UIManager(void)
 : mCurLayout( NULL ), mGameShutdown( false )
 {

 }


UIManager::~UIManager(void)
{
    // stub
}





//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================


void UIManager::Initialize(void)
{

    LogInfo( "The UIManager initialization has started" );

    // Create Master List
    AddLayout( new UIBattleScreenLayout() );
    AddLayout( new UITitleScreenLayout() );
    AddLayout( new UIMainMenuLayout() );
    AddLayout( new UIWinLayout() );
    AddLayout( new UILoseLayout() );
    AddLayout( new UIPasswordVerificationLayout() );
    AddLayout( new UISetPasswordLayout() );
    AddLayout( new UIOverMapLayout() );
    AddLayout( new UIPartyStatusLayout() );
    AddLayout( new UIProfileMenuLayout() );
    AddLayout( new UINewProfileLayout() );
    AddLayout( new UILoadProfileLayout() );
    AddLayout( new UITutorialMenuLayout() );
    AddLayout( new UITutorialLayout() );
    AddLayout( new UILoadGameLayout() );
    AddLayout( new UICreditsLayout() );
    AddLayout( new UIOptionsLayout() );
    AddLayout( new UISaveGameLayout() );
    AddLayout( new UIArmoryLayout() );
    AddLayout( new UIMarketLayout() );



    //PushLayout("PasswordVer");
    PushLayout("TitleScreen");

    // Add all the layouts to the manager.
    LogInfo( "The UIManager has been initialized successfully." );

}

void UIManager::Shutdown(void)
{
    LogInfo( "The UIManager shutdown has started" );
    // Delete all the objects withing UIManager

    // At the moment I'm not using the UIManager master list, but I'll change this if I am
    for ( UILayoutItr iter = mLayoutMasterList.begin(); iter!=mLayoutMasterList.end(); ++iter )
    {
        if( *iter )
        {
            delete (*iter);
        }
    }

    mCurrentLayoutList.clear();
    mCurLayout = NULL;

    // Delete this instance
    delete _instance;
    _instance = NULL;

    LogInfo( "The UIManager has been shut down successfully." );

}

/*void UIManager::Render(void)
{

}*/


//============================= ACCESS     ===================================


void UIManager::PushLayout(UILayout* newLayout)
{

    if (mCurLayout!=NULL)
    {
        mCurLayout->OnClose();
    }
    mCurLayout = NULL;
    mCurrentLayoutList.push_front(newLayout);

    mCurLayout = mCurrentLayoutList.front();
    if (mCurLayout!=NULL)
    {
        mCurLayout->OnLoad();
    }
    else
    {
        printf("Layout failed to load: pointer\n");
    }
}

void UIManager::PushLayout(const std::string & newLayout)
{

    UILayout *temp = GetLayout(newLayout);
    if (temp!=NULL)
    {
        PushLayout( temp );
    }
    else
    {
        printf("Layout failed to load: string\n");
    }

}

void UIManager::PopAllLayouts(void)
{
    if (mCurLayout)
    {
        mCurLayout->OnClose();
    }
    mCurrentLayoutList.clear();
    PushLayout("TitleScreen");

}



void UIManager::PopLayout(void)
{


    mCurrentLayoutList.pop_front();
    if (mCurLayout!=NULL)
    {
        mCurLayout->OnClose();
    }
    else
    {
        printf("Current Layout had an error");
    }
    mCurLayout = mCurrentLayoutList.front();


    if (mCurLayout==NULL)
    {
        PushLayout("TitleScreen");
    }
    else
    {
        mCurLayout->OnLoad();
    }



}

void UIManager::AddLayout(UILayout* newLayout)
{
    mLayoutMasterList.push_back(newLayout);

}

void UIManager::RemoveLayout(UILayout* removeLayout)
{
    // Do it later....
}

void UIManager::Update()
{
    if( mCurLayout )
    {
        mCurLayout->Update();
    }
}

//============================= INQUIRY    ===================================


UILayout* UIManager::PeekLayout(void)
{
    return mCurLayout;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

UILayout* UIManager::GetLayout(const std::string & layoutName)
{
    string compare;

    for ( UILayoutItr iter = mLayoutMasterList.begin(); iter!=mLayoutMasterList.end(); ++iter )
    {
        compare = (*iter)->GetName();
        if (compare==layoutName)
        {
            return (*iter);
        }
    }

    return NULL;

}


/////////////////////////////// PRIVATE    ///////////////////////////////////
