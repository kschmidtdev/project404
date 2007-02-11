/**
 * File: UITitleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UITitleScreenLayout.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITitleScreenLayout::UITitleScreenLayout()
{
    elements.push_back( new UIElement("nicePic.bmp") );
}// UITitleScreenLayout

UITitleScreenLayout::UITitleScreenLayout(const UITitleScreenLayout&)
{
}// UITitleScreenLayout

UITitleScreenLayout::~UITitleScreenLayout()
{
}// ~UITitleScreenLayout


//============================= OPERATORS ====================================

/*UITitleScreenLayout&
UITitleScreenLayout::operator=(UITitleScreenLayout&);
{
   return *this;

}// =*/

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
