/**
 * File: UIImage.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added "SetImage" method to dynamically adjust image
 */

#include "UIImage.h"                                // class implemented

#include <util.h>

#include <ResourceManager/ResourceManager.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIImage::UIImage()
{
}// UIImage


UIImage::UIImage( const std::string & filename)
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}

UIImage::~UIImage()
{
}// ~UIImage


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================

void UIImage::SetImage(const std::string & filename)
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
