/**
 * File: UIImage.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 */

#include <util.h>


#include "UIImage.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIImage::UIImage()
{
}// UIImage


UIImage::UIImage( const string filename)
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}

UIImage::~UIImage()
{
}// ~UIImage


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
