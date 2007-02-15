/**
 * File: UITitleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 10 2007 | Documentation
 * Andrew Osborne, February 14 2007 | Added ProcessEvent method
 * Andrew Osborne, February 14 2007 | Made final version for title screen
*/
#include "UITitleScreenLayout.h"                                // class implemented
#include "UIImage.h"
#include "UIManager.h"
#include "UIText.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITitleScreenLayout::UITitleScreenLayout()
{
    mName = "TitleScreen";

    //UIImage *temp = new UIImage("nicePic.bmp");
    UIImage *temp = new UIImage("castle.bmp");
    temp->SetPos( Point(20, 16) );
    mElements.push_back(temp);

    UIText *tempText = new UIText("SymTac", 100, 255, 0, 0);
    tempText->SetPos( Point(120,50) );
    //SDL_Surface *tempSur = tempText->GetElement();
    //printf("title: width: %d, height: %d\n", tempSur->w, tempSur->h);
    mElements.push_back(tempText);

    tempText = new UIText("Press CONFIRM to advance", 24, 255, 0, 0);
    tempText->SetPos( Point(165, 390) );
    //tempSur = tempText->GetElement();
    //printf("confirm: width: %d, height: %d\n", tempSur->w, tempSur->h);
    mElements.push_back(tempText);


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

void UITitleScreenLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PushLayout("MainMenu");
            break;
        default:
            break;
    }

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
