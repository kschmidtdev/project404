/**
 * File: UIGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UIGrid.h"                                // class implemented
#include "UITile.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIGrid::UIGrid()
: mNumRows( 3 ), mNumColumns( 3 )
{
    // Add all elements
    SDL_Surface *sample = ResourceManager::GetInstance()->LoadTexture("defaultTile.bmp");

    mTileHeight = sample->h;
    mTileWidth = sample->w;
    int i, j;

    //tiles = new UITile*[mNumColumns];
    //for (i=0; i<mNumColumns; i++)



    int tileSpacing = 20;

    int startXoffset = 20;
    int startYoffset = 20;

    UITile *temp;

    for (i=0; i<mNumColumns; i++)
    {
        //tiles[i] = new UITile[mNumRows];
        for (j=0; j<mNumRows; j++)
        {
            temp = new UITile();
            temp->setPos( Point(startXoffset + i*(tileSpacing + mTileWidth), startYoffset + j*(tileSpacing + mTileHeight) ) );
            //tiles[i][j] = temp;
            mTiles.push_back( temp );
        }
    }

    // Assign self an image
    elementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.bmp");

}// UIGrid


UIGrid::~UIGrid()
{
}// ~UIGrid


//============================= OPERATORS ====================================

void UIGrid::RenderSelf(SDL_Surface* destination)
{
    // The menu must be rendered first
    SDLRenderer::GetInstance()->DrawImageAt(elementImage, pos.GetX(), pos.GetY(), elementImage->w, elementImage->h, destination);

    // Cursor is rendered second
    //cursor->RenderSelf(destination);

    // Buttons are rendered second
    std::vector<UITile*>::iterator iter;
    //int size = buttons.size();

    for (iter = mTiles.begin();
            iter!=mTiles.end(); iter++)
    {
        (*iter)->RenderSelf(destination);
    }

}

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
