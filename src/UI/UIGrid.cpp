/**
 * File: UIGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, February 11 2007 | Added checks to prevent crashing if textures are not loaded
 * Andrew osborne, February 11 2007 | Added Destructor and documentaton
 * Andrew Osborne, February 12 2007 | Setup characters, allowed movement, created a number of helper functions
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

    // Move Range
    std::vector<UIImage*>::iterator iIter;
    iIter = mImageMoveRange.begin();
    while (iIter!=mImageMoveRange.end())
    {
        delete (*iIter);
        iIter++;
    }

    // Attack Range
    iIter = mImageAttackRange.begin();
    while (iIter!=mImageMoveRange.end())
    {
        delete (*iIter);
        iIter++;
    }


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

    // Moveable/Attackable Ranges are rendered first
    int curState = mLevel->ReturnState();
    std::vector<UIImage*>::iterator iIter;

    if (curState==1)
    {
        // View Moveable Tiles
        iIter = mImageMoveRange.begin();
        while (iIter!=mImageMoveRange.end())
        {
            (*iIter)->RenderSelf(destination);
            iIter++;
        }
    }
    else if (curState==2)
    {
        // Vies Attackable Tiles
        iIter = mImageAttackRange.begin();
        while (iIter!=mImageAttackRange.end())
        {
            (*iIter)->RenderSelf(destination);
            iIter++;
        }
    }

    // Cursor is rendered second
    mCursor->RenderSelf(destination);

    // Tiles are rendered third
    std::vector<UITile*>::iterator iter;

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
        case InputManager::CONFIRM:
            confirmFunction(mCursorPos);
            break;
        case InputManager::CANCEL:
            // Will be handled later
            // Add a request to confirm quiting??
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

void UIGrid::AddRange( vector<Point> pointRange, vector<UIImage*> elementRange)
{

    int numOfNeededRangeSquares = pointRange.size();
    int numOfCurrentRangeSqaures = elementRange.size();
    int i;
    bool isMoveRange;

    printf("needed: %d, current: %d\n", numOfNeededRangeSquares, numOfCurrentRangeSqaures);

    // If more new Blue tiles/cursors are needed more are created

    if (numOfNeededRangeSquares>numOfCurrentRangeSqaures) {
        // Need more squares
        //printf("before condition Statement\n");
        // Determing image file based on range
        string imageName;
        if (elementRange==mImageMoveRange)
        {
            imageName = "blueCursor.bmp";
            isMoveRange = true;
        }
        else if (elementRange==mImageAttackRange)
        {
            imageName = "yellowCursor.bmp";
            isMoveRange = false;

        } else {
            //printf("neither condition statisfied\n");
        }
        //printf("after condition statement\n");

        int newSquares = numOfNeededRangeSquares - numOfCurrentRangeSqaures;
        for (i=0; i<newSquares; i++)
            elementRange.push_back( new UIImage(imageName) );

    }

    std::vector<Point>::iterator pointIter;
    std::vector<UIImage*>::iterator elementIter;
    Point cursorPos;
    Point gridPoint;

    pointIter = pointRange.begin();

    elementIter = elementRange.begin();

    for (i=0; i<numOfNeededRangeSquares; i++)
    {
        gridPoint = (*pointIter);
        cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
        (*elementIter)->setPos( cursorPos );
        (*elementIter)->setVisible( true );
        elementIter++;
        pointIter++;
    }

    // for remainder of unused elements, set invisible
    while (elementIter!=elementRange.end())
    {
        (*elementIter)->setVisible( false );
        elementIter++;
    }

    if (isMoveRange) {
        mImageMoveRange = elementRange;
    } else {
        mImageAttackRange = elementRange;
    }


}


void UIGrid::ClearMoveableRange(void) {

    std::vector<UIImage*>::iterator iter;

    iter = mImageMoveRange.begin();

    while (iter!=mImageMoveRange.end()) {
        (*iter)->setVisible( false );
        iter++;
    }

}


void UIGrid::ClearAttackRange(void) {

    std::vector<UIImage*>::iterator iter;

    iter = mImageAttackRange.begin();

    while (iter!=mImageAttackRange.end()) {
        (*iter)->setVisible( false );
        iter++;
    }

}

void UIGrid::AddAttackRange(vector<Point> moveRange)
{
    AddRange( moveRange, mImageAttackRange);
}


void UIGrid::AddMoveableRange(vector<Point> moveRange)
{

    AddRange( moveRange, mImageMoveRange);

    /*int numOfNeededRangeSquares = moveRange.size();
    int numOfCurrentRangeSqaures = mImageMoveRange.size();
    int i;
    printf("needed: %d, current: %d\n", numOfNeededRangeSquares, numOfCurrentRangeSqaures);

    // If more new Blue tiles/cursors are needed more are created
    if (numOfNeededRangeSquares>numOfCurrentRangeSqaures) {
        // Need more squares
        int newSquares = numOfNeededRangeSquares - numOfCurrentRangeSqaures;
        for (i=0; i<newSquares; i++)
            mImageMoveRange.push_back( new UIImage("blueCursor.bmp") );

    }

    std::vector<Point>::iterator pointIter;
    std::vector<UIImage*>::iterator elementIter;
    Point cursorPos;
    Point gridPoint;

    pointIter = moveRange.begin();
    elementIter = mImageMoveRange.begin();

    for (i=0; i<numOfNeededRangeSquares; i++)
    {
        gridPoint = (*pointIter);
        cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
        (*elementIter)->setPos( cursorPos );
        (*elementIter)->setVisible( true );
        elementIter++;
        pointIter++;
    }

    // for remainder of unused elements, set invisible
    while (elementIter!=mImageMoveRange.end())
    {
        (*elementIter)->setVisible( false );
        elementIter++;
    }*/

}




//============================= ACCESS     ===================================

void UIGrid::setLevel(Level* l)
{
    mLevel = l;
}

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
    //Level *mLevel = NULL;

    // tHIS function should not be called at this point

    int curState = mLevel->ReturnState();
    printf("current State:%d\n", curState);
    printf("current Point: %d, %d:\n", p.GetX(), p.GetY() );

    bool validAction = false;

    Character* tempChar;
    switch(curState) {
        case 0:
            // Attempt to select character
            tempChar = mLevel->OnSelect(p);
            if (tempChar==NULL) {
                // Unsuccessful, do nothing
                printf("not a character\n");
            } else {
                printf("character selected\n");
                // Successful, display move range
                vector<Point> moveArea = mLevel->GetMoveArea();
                AddMoveableRange( moveArea );
                mMoveRange = moveArea;
                mCurCharacter = tempChar;
            }
            break;
        case 1:
            // Attempting to move to new spot

            // Check if move was cancelled
            if (p==mCurCharacter->GetPoint()) {

                mLevel->OnSelect(p);

            } else {

                // Check to see if valid spot for movement
                std::vector<Point>::iterator iter;


                for (iter = mMoveRange.begin();
                        iter!=mMoveRange.end(); iter++)
                {
                    printf("movePoint: %d, %d\n", (*iter).GetX(), (*iter).GetY() );
                    if (p==(*iter))
                        validAction = true;
                }

                //printf("Valid Move?:%d", validAction);

                if ( validAction ) {
                    // remove icon from old spot
                    removeCharacter( mCurCharacter->GetPoint() );

                    // add icon to new spot
                    Point old = mCurCharacter->GetPoint();
                    mCurCharacter->Move(p);
                    addCharacter( mCurCharacter );
                    mCurCharacter->Move(old);
                    mLevel->OnSelect(p);
                    ClearMoveableRange();
                    printf("curState after move:%d\n", mLevel->ReturnState());

                    // Prep screen for attack
                    AddAttackRange( mLevel->GetAttackArea() );

                } else {
                    // do nothing
                    // maybe display message later....
                }
            }

            break;

        case 2:
            // Attempting to attack

            // check to see if attack-range is valid
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
