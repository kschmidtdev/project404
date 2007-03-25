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
 * Karl Schmidt, February 13 2007    | Implemented typedefs for vector types, destructor modification
 * Karl Schmidt, February 14 2007    | Updated function capitalization, block style, typedefs, refs
 * Karl Schmidt, March 22 2007       | Correcting include orders and paths
 * Andrew Osborne, March 23 2007     | Fixed undiscovered bug (should have initialized mDefaultEvent - to NULL)
 * Andrew Osborne, March 23 2007     | Cleaned out some commented code and added proper SetEventHandler method ( to work with
 *                                      UIEventListener(s)
 */

#include "UILayout.h"                                   // class implemented

#include <util.h>

#include <Renderer/SDLRenderer.h>
#include <UI/UIManager.h>
#include <UI/UIElement.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILayout::UILayout(void)
: mDefaultEventListener( NULL )
{

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

    if(mDefaultEventListener)
    {
        mDefaultEventListener->ProcessEvent(evt);
    }

}

//============================= ACCESS     ===================================


void UILayout::SetEventHandler( UIEventListener *newEvent )
{
    mDefaultEventListener->Disable();
    mDefaultEventListener=newEvent;
    mDefaultEventListener->Enable();
}

//============================= INQUIRY    ===================================

const std::string & UILayout::GetName(void) const
{
    return mName;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////


