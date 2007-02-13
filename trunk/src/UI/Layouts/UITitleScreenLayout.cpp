/**
 * File: UITitleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 10 2007 | Documentation
*/
#include "UITitleScreenLayout.h"                                // class implemented
#include "UIImage.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITitleScreenLayout::UITitleScreenLayout()
{
    mName = "TitleScreen";

    UIImage *temp = new UIImage("nicePic.bmp");
    mElements.push_back(temp);

}// UITitleScreenLayout

UITitleScreenLayout::~UITitleScreenLayout()
{
}// ~UITitleScreenLayout


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

/*void UITitleScreenLayout::RenderSelf( SDL_Surface* destination )
{
    // stub
}*/


//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
