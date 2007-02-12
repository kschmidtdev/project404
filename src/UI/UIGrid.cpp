/**
 * File: UIGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 * Karl Schmidt, February 11 2007 | Added checks to prevent crashing if textures are not loaded
 */
#include "UIGrid.h"                                // class implemented
#include "UITile.h"
#include "UICursor.h"
#include "InputManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIGrid::UIGrid()
: mNumRows( 10 ), mNumColumns( 10 ), mCursorPos( Point(0,0) ), mTileStart( Point(10,10) ), mTileOffset( 2 )
{
    // Add all elements
    SDL_Surface *sample = ResourceManager::GetInstance()->LoadTexture("defaultTile.bmp");

    if( sample )
    {
        mTileHeight = sample->h;
        mTileWidth = sample->w;
    }

    int i, j;




    //int tileSpacing = 2;

    // Set Tiles in place
    // --------------------------------------------------
    int startXoffset = mTileStart.GetX();
    int startYoffset = mTileStart.GetY();
    mTotalTileOffset = mTileOffset + mTileWidth;

    UITile *temp;

    for (i=0; i<mNumColumns; i++)
    {
        //tiles[i] = new UITile[mNumRows];
        for (j=0; j<mNumRows; j++)
        {
            temp = new UITile();
            temp->setPos( Point(startXoffset + i*(mTotalTileOffset), startYoffset + j*(mTotalTileOffset) ) );
            //tiles[i][j] = temp;
            mTiles.push_back( temp );
        }
    }

    // Assign self an image
    // ----------------------------------------------------
    elementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.bmp");

    // Assign Cursor its place
    // ----------------------------------------------------
    mMaxCursorPos.Set(mNumColumns - 1, mNumRows - 1);
    mCursorStart = mTileStart + Point( -mTileOffset, -mTileOffset);
    mCursor = new UICursor("tileCursor.bmp", "");
    mCursor->setPos( mCursorStart );

    // Retrieve Game Engine
    //mGameEngine = GameEngine::GetInstance();
    //mGameEngine = NULL;

}// UIGrid


UIGrid::~UIGrid()
{
}// ~UIGrid


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================

void UIGrid::RenderSelf(SDL_Surface* destination)
{
    if( elementImage )
    {
        // The menu must be rendered first
        //SDLRenderer::GetInstance()->DrawImageAt(elementImage, pos.GetX(), pos.GetY(), elementImage->w, elementImage->h, destination);
    }

    // Cursor is rendered second
    mCursor->RenderSelf(destination);

    // Buttons are rendered second
    std::vector<UITile*>::iterator iter;
    //int size = buttons.size();

    for (iter = mTiles.begin();
            iter!=mTiles.end(); iter++)
    {
        (*iter)->RenderSelf(destination);
    }

}

void UIGrid::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    // Come back to this later
    Point newPos;
    switch(evt) {
        case InputManager::UP:
            // Move cursor up
            if (mCursorPos.GetY()>0) {
                mCursorPos = mCursorPos + Point(0,-1);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::DOWN:
            if (mCursorPos.GetY()<mMaxCursorPos.GetY()) {
                mCursorPos = mCursorPos + Point(0,1);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            break;
        case InputManager::LEFT:
            // Move cursor up
            if (mCursorPos.GetX()>0) {
                mCursorPos = mCursorPos + Point(-1,0);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::RIGHT:
            if (mCursorPos.GetX()<mMaxCursorPos.GetX()) {
                mCursorPos = mCursorPos + Point(1,0);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            break;
        default:
            break;

    }
}


//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
