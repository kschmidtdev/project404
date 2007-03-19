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
 */

#include <util.h>


#include <UIManager.h>                                  // class implemented
#include <Logger.h>
#include <UIBattleScreenLayout.h>
#include <UITitleScreenLayout.h>
#include <UIMainMenuLayout.h>
#include <UIWinLayout.h>
#include <UILoseLayout.h>
#include <UIPasswordVerificationLayout.h>
#include <UISetPasswordLayout.h>
#include <UIOverMapLayout.h>
#include <UIPartyStatusLayout.h>
#include <UIProfileMenuLayout.h>
#include <UINewProfileLayout.h>
#include <UILoadProfileLayout.h>
#include <UITutorialMenuLayout.h>
#include <UITutorialLayout.h>
#include <UILoadGameLayout.h>
#include <UICreditsLayout.h>
#include <UIOptionsLayout.h>
#include <UISaveGameLayout.h>
#include <UIArmoryLayout.h>
#include <UIMarketLayout.h>
#include <vector>


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
    PushLayout("ProfileMenu");

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

void UIManager::PushLayout(const string newLayout)
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

//============================= INQUIRY    ===================================


UILayout* UIManager::PeekLayout(void)
{
    return mCurLayout;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

UILayout* UIManager::GetLayout(const string layoutName)
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
