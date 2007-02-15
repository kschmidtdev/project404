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
 */

#include <UIManager.h>                                  // class implemented
#include <../Logger.h>
#include <UIBattleScreenLayout.h>
#include <UITitleScreenLayout.h>
#include <UIMainMenuLayout.h>
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

     // Constructor stuff

     // Add title screen or profile menu
     //Logger::GetInstance()->LogMessage(Logger::INFO, "UIManager Initiated");


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

    // Set current (first) layout
    PushLayout("BattleScreen");

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

void UIManager::Render(void)
{

    // or RenderSelf()
    //mCurLayout->RenderSelf();

}


//============================= ACCESS     ===================================


void UIManager::PushLayout(UILayout* newLayout)
{

    mCurrentLayoutList.push_front(newLayout);
    mCurLayout = mCurrentLayoutList.front();
    mCurLayout->OnLoad();

}

void UIManager::PushLayout(const string newLayout)
{

    PushLayout( GetLayout(newLayout) );

}

void UIManager::PopLayout(void)
{

    mCurrentLayoutList.pop_front();
    mCurLayout->OnClose();
    mCurLayout = mCurrentLayoutList.front();

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
