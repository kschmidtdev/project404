/**
 * File: UIMenu.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10, 2007 | Initial creation and testing
 */
#include "UIMenu.h"                                // class implemented
#include "Point.h"
//#include "ResourceManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIMenu::UIMenu()
{

    curCursorPosition = 1;
    Point tempPoint(0,0);

    // Create cursor
    cursor = new UIElement("cursor.bmp");
    tempPoint.Set(40, 20);
    cursor ->setPos( tempPoint );

    // Create button
    UIElement *tempButton;
    for (int i=0; i<3; i++)
    {
        tempButton = new UIElement("testButton.bmp");
        tempPoint.Set(50, 30 + i*70);
        tempButton->setPos( tempPoint );
        buttons.push_back( tempButton );
    }

    // Set backgound
    elementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.bmp");



}// UIMenu

UIMenu::~UIMenu()
{
}// ~UIMenu


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UIMenu::RenderSelf(SDL_Surface* destination)
{
    // The menu must be rendered first
    rend->DrawImageAt(elementImage, pos.GetX(), pos.GetY(), elementImage->w, elementImage->h, destination);

    // Cursor is rendered second
    cursor->RenderSelf(elementImage);

    // Buttons are rendered second
    std::vector<UIElement*>::iterator iter;
    //int size = buttons.size();

    for (iter = buttons.begin();
            iter!=buttons.end(); iter++)
    {
        (*iter)->RenderSelf(elementImage);
    }

}

void UIMenu::inputFunction(void)
{

}


//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
