/**
 * File: UILayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 7, 2007 | Initial creation
 * Andrew Osborne, February 10, 2007 | Got it to work
 * Andrew Osborne, February 10, 2007 | Added documentation
 * Andrew Osborne, February 11, 2007 | Added Process event handling, took out renderSelf
 * Andrew Osborne, February 12, 2007 | Added getName for searching purposes
 */


#include <UILayout.h>                                   // class implemented
#include <Renderer/SDLRenderer.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILayout::UILayout(void)
{

        // Code that will be taken out at some point
   // mElements.push_back(
}

UILayout::~UILayout(void)
{
    std::vector<UIElement*>::iterator iter;

    for (iter = mElements.begin();
            iter!=mElements.end(); iter++)
    {
        delete *iter;
    }

    mDefaultEventListener = NULL;
}


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================


/*void UILayout::RenderSelf(SDL_Surface* destination)
{
    // Needs to be overridden
    // Display background Image
}*/


void UILayout::onLoad(void)
{
    // Iterate through elements in layout
    // and add them to renderer queue

    std::vector<UIElement*>::iterator iter;
    SDLRenderer *rend = SDLRenderer::GetInstance();

    InputManager::GetInstance()->AddEventListener(this);

    for (iter = mElements.begin();
            iter!=mElements.end(); iter++)
    {
        rend->AddToRenderQueue( (*iter) );
    }


}

void UILayout::onClose(void)
{
    // Iterate through elements in layout
    // and remove them from renderer

    std::vector<UIElement*>::iterator iter;
    SDLRenderer *rend = SDLRenderer::GetInstance();

    InputManager::GetInstance()->RemoveEventListener(this);

    for (iter = mElements.begin();
            iter!=mElements.end(); iter++)
    {
        rend->RemoveFromRenderQueue( (*iter) );
    }

}


void UILayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    if (mDefaultEventListener!=NULL)
        mDefaultEventListener->ProcessEvent(evt);

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================

string UILayout::getName(void)
{
    return mName;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////


