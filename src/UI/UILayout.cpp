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
 */


#include <UILayout.h>                                   // class implemented
#include <Renderer/SDLRenderer.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILayout::UILayout(void)
{

        // Code that will be taken out at some point
   // elements.push_back(
}

UILayout::~UILayout(void)
{
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

    for (iter = elements.begin();
            iter!=elements.end(); iter++)
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

    for (iter = elements.begin();
            iter!=elements.end(); iter++)
    {
        rend->RemoveFromRenderQueue( (*iter) );
    }

}


void UILayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    if (defaultEventListener!=NULL)
        defaultEventListener->ProcessEvent(evt);

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////


