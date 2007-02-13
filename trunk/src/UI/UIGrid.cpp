/**
 * File: UIGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, February 11 2007 | Added checks to prevent crashing if textures are not loaded
 * Andrew osborne, February 11 2007 | Added Destructor and documentaton
 */
#include "UIGrid.h"                                // class implemented
#include "UITile.h"
#include "UICursor.h"
#include "UIManager.h"
#include "InputManager.h"
#include "GameEngine/Level.h"

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
    mElementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.bmp");

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
    // Release Tiles
    std::vector<UITile*>::iterator iter;
    for (iter = mTiles.begin();
            iter!=mTiles.end(); iter++)
    {
        delete *iter;
    }

    delete mCursor;
    mCursor = NULL;



}// ~UIGrid


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================

void UIGrid::RenderSelf(SDL_Surface* destination)
{
    if( mElementImage )
    {
        // The menu must be rendered first
        //SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
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


void UIGrid::addCharacter( Character *c)
{
    Point p = c->GetPoint();

    if ( validPoint(p)  )
    {
        int index = findIndex( p.GetX(), p.GetY() );
        //printf("index: %d, maxSize: %d\n", index, mTiles.size());
        UITile* temp = mTiles[index];
        temp->addCharacter( getClassSurface(c) );
    }
}

void UIGrid::removeCharacter(Point p) {

    int x = p.GetX();
    int y = p.GetY();

    if ( validPoint(p) )
    {
        int index = findIndex( x, y );
        UITile* temp = mTiles[index];
        temp->removeCharacter();
    }
}


//============================= ACCESS     ===================================

/*void UIGrid::setParent(UIBattleScreenLayout *parent)
{
    mBattleLayout = parent;
}*/

//============================= INQUIRY    ===================================

bool UIGrid::validPoint(Point p)
{
    if ( (p.GetX()<mNumColumns) && (p.GetY()<mNumRows) )
    {
        return true;
    } else {
        return false;
    }
}


/////////////////////////////// PROTECTED  ///////////////////////////////////


int UIGrid::findIndex(int x, int y)
{
    return y + mNumRows*x;
}

void UIGrid::confirmFunction(Point p)
{

    //UILayout *tempLayout = UIManager::GetInstance()->getLayout("BattleScreen");
    Level *mLevel = NULL;

    // tHIS function should not be called at this point

    int curState = mLevel->ReturnState();
    bool validAction = false;

    Character* tempChar;
    switch(curState) {
        case 0:
            // Attempt to select character
            tempChar = mLevel->OnSelect(p);
            if (tempChar==NULL) {
                // Unsuccessful, do nothing
            } else {
                // Successful, display move range
                vector<Point> moveArea = mLevel->GetMoveArea();
                //AddMoveableRange( moveArea );
                mCurCharacter = tempChar;
            }
            break;
        case 1:
            // Attempting to move to new spot


            // Check to see if valid spot for movement

            if ( validAction ) {
                // remove icon from old spot
                removeCharacter( mCurCharacter->GetPoint() );

                // add icon to new spot
                mCurCharacter->Move(p);
                addCharacter( mCurCharacter );

            } else {
                // do nothing
                // maybe display message later....
            }


            break;

        case 2:
            // Attempting to attack

            // check to see if attack-range is valid


            // now check if person is there
            Character* target = mLevel->OnSelect(p);
            if ( (validAction) && (target!=NULL) )
            {

                // no

            }

            // Check for end game

            // Check for end turn

            break;

    }
}

SDL_Surface* UIGrid::getClassSurface(Character* c)
{
    string temp = c->GetClassName();

    if (temp=="Archer") {
        return ResourceManager::GetInstance()->LoadTexture("archer.bmp");
    } else if (temp=="Knight") {
        return ResourceManager::GetInstance()->LoadTexture("knight.bmp");
    } else if (temp=="Healer") {
        return ResourceManager::GetInstance()->LoadTexture("healer.bmp");
    } else if (temp=="Mage") {
        return ResourceManager::GetInstance()->LoadTexture("mage.bmp");
    } else {
        // you screwed up
        return ResourceManager::GetInstance()->LoadTexture("charTile.bmp");
    }

}

/////////////////////////////// PRIVATE    ///////////////////////////////////
