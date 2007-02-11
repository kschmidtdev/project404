/**
 * File: UIManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10, 2007 | Initial creation and testing
 * Andrew Osborne, February 10, 2007 | Added some comments, deleted inputFunction
 */

#include <UIManager.h>                                  // class implemented
#include <../Logger.h>



/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================


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

    // Add all the layouts to the manager.

}

void UIManager::Shutdown(void)
{

    // Remove all the elements from the stack/list
    // Delete them too? - yes
    /*std::list<UILayout*>::iterator iter;
    //int size = elements.size();

    for (iter = elements.begin();
            iter!=elements.end(); iter++)
    {
        delete (*iter);
    }*/



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
