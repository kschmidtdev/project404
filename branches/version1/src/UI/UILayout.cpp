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
 * Karl Schmidt, February 13 2007 | Implemented typedefs for vector types, destructor modification
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 */


#include <UILayout.h>                                   // class implemented
#include <Renderer/SDLRenderer.h>
#include <UIManager.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILayout::UILayout(void)
{

        // Code that will be taken out at some point
   // mElements.push_back(
}

UILayout::~UILayout(void)
{
    for( UIElementPtrItr i = mElements.begin(); i != mElements.end(); ++i )
    {
        if( *i )
        {
            delete *i;
        }
    }

    mDefaultEventListener = NULL;
}


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UILayout::OnLoad(void)
{
    // Iterate through elements in layout
    // and add them to renderer queue

    SDLRenderer *rend = SDLRenderer::GetInstance();

    InputManager::GetInstance()->AddEventListener(this);

    for ( UIElementPtrItr iter = mElements.begin(); iter!=mElements.end(); ++iter)
    {
        rend->AddToRenderQueue( (*iter) );
    }


}

void UILayout::OnClose(void)
{
    // Iterate through elements in layout
    // and remove them from renderer

    SDLRenderer *rend = SDLRenderer::GetInstance();

    InputManager::GetInstance()->RemoveEventListener(this);

    for ( UIElementPtrItr iter = mElements.begin(); iter!=mElements.end(); ++iter )
    {
        rend->RemoveFromRenderQueue( (*iter) );
    }

}


void UILayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    if( mDefaultEventListener != NULL )
    {
        mDefaultEventListener->ProcessEvent(evt);
    }

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================

string UILayout::GetName(void)
{
    return mName;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////


