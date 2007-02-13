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

    LogInfo( "The UIManager initializatio has started" );

    // Create Master List
    addLayout( new UIBattleScreenLayout() );
    addLayout( new UITitleScreenLayout() );
    addLayout( new UIMainMenuLayout() );

    // Set current (first) layout
    pushLayout("BattleScreen");

    // Add all the layouts to the manager.
    LogInfo( "The UIManager has been initialized successfully." );

}

void UIManager::Shutdown(void)
{

    // Delete all the objects withing UIManager

    // At the moment I'm not using the UIManager master list, but I'll change this if I am
    std::list<UILayout*>::iterator iter;

    for (iter = mCurrentLayoutList.begin();
            iter!=mCurrentLayoutList.end(); iter++)
    {
        delete (*iter);
    }
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


void UIManager::pushLayout(UILayout* newLayout)
{

    mCurrentLayoutList.push_front(newLayout);
    mCurLayout = mCurrentLayoutList.front();
    mCurLayout->onLoad();

}

void UIManager::pushLayout(const string newLayout)
{

    pushLayout( getLayout(newLayout) );

}

void UIManager::popLayout(void)
{

    mCurrentLayoutList.pop_front();
    mCurLayout->onClose();
    mCurLayout = mCurrentLayoutList.front();

}

void UIManager::addLayout(UILayout* newLayout)
{
    mLayoutMasterList.push_back(newLayout);

}

void UIManager::removeLayout(UILayout* removeLayout)
{

        // Do it later....
}

//============================= INQUIRY    ===================================


UILayout* UIManager::peekLayout(void)
{
    return mCurLayout;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

UILayout* UIManager::getLayout(const string layoutName)
{
    std::vector<UILayout*>::iterator iter;
    string compare;

    for (iter = mLayoutMasterList.begin();
            iter!=mLayoutMasterList.end(); iter++)
    {
        compare = (*iter)->getName();
        if (compare==layoutName)
            return (*iter);

    }

    return NULL;

}


/////////////////////////////// PRIVATE    ///////////////////////////////////
