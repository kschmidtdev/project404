/**
 * File: Renderer.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 8 2007 | Initial creation of renderer
 */
#include "Renderer.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Renderer::Renderer()
: mXRes( 640 ),
  mYRes( 480 ),
  mColourDepth( 32 )
{
}// Renderer

Renderer::~Renderer()
{
}// ~Renderer

void Renderer::Initialize( const int xRes, const int yRes, const int colourDepth )
{
    mXRes = xRes;
    mYRes = yRes;
    mColourDepth = colourDepth;
}


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
