/**
 * File: UIManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10, 2007 | Initial creation and testing
 * Andrew Osborne, February 10, 2007 | Added some comments, deleted inputFunction
 * Andrew Osborne, February 11 2007 | Added GetInstance method
 */

#include <UIManager.h>                                  // class implemented
#include <../Logger.h>
#include <UIBattleScreenLayout.h> // temp fix



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

     // Destructor stuff

     // Add title screen or profile menu
     //Logger::GetInstance()->LogMessage(Logger::INFO, "UIManager Initiated");


 }





//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================


void UIManager::Initialize(void)
{

    // I don't know
    pushLayout( new UIBattleScreenLayout() );

    // Add all the layouts to the manager.
    LogInfo( "The UIManager has been initialized successfully." );

}

void UIManager::Shutdown(void)
{

    // Delete all the objects withing UIManager

    // To be implemented later

    // Delete this instance
    delete _instance;
    _instance = NULL;
    LogInfo( "The UIManager has been shut down successfully." );

}

void UIManager::Render(void)
{

    // or RenderSelf()
    //curLayout->RenderSelf();

}


//============================= ACCESS     ===================================


void UIManager::pushLayout(UILayout* newLayout)
{

    CurrentLayoutList.push_front(newLayout);
    curLayout = CurrentLayoutList.front();
    curLayout->onLoad();

}

void UIManager::popLayout(void)
{

    CurrentLayoutList.pop_front();
    curLayout->onClose();
    curLayout = CurrentLayoutList.front();

}

void UIManager::addLayout(UILayout* newLayout)
{
    LayoutMasterList.push_back(newLayout);

}

void UIManager::removeLayout(UILayout* removeLayout)
{

        // Do it later....
}

//============================= INQUIRY    ===================================


UILayout* UIManager::peekLayout(void)
{
    return curLayout;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
