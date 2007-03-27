/**
 * File: UIOptionsLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 24 2007, Proper UI Implementation
 * Karl Schmidt, March 26 2007   | Added sound manager hooks for volume setting, selecting current setting
 								   on open support as well
 */
#include "UIOptionsLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>

#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>

#include <SoundManager.h>

class SwitchToFunction : public FuncObj
{
public:
    SwitchToFunction(UILayout *layout, UIEventListener* newListener)
    : mLayout(layout), mNewListener( newListener )
    {
    }

    void operator()(void)
    {
        if ( (mLayout) && (mNewListener) )
            mLayout->SetEventHandler(mNewListener);
    }


protected:
    UILayout* mLayout;
    UIEventListener* mNewListener;

};



class SelectDifficultyFunction : public FuncObj
{
public:
    SelectDifficultyFunction(int diff, UIMenu* parent)
    : mDifficulty(diff), mParentMenu( parent )
    {
    }

    void operator()(void)
    {
        //GameEngine::GetInstance()->SelectDifficult(mDifficulty)
        if (mParentMenu)
            mParentMenu->ProcessEvent(InputManager::CANCEL);
    }


protected:
    int mDifficulty;
    UIMenu *mParentMenu;

};


class SelectSoundLevelFunction : public FuncObj
{
public:
    SelectSoundLevelFunction( SoundManager::VOLUME_LEVEL volume, UIMenu* parent)
    : mSoundLevel(volume), mParentMenu( parent )
    {
    }

    void operator()(void)
    {
        if (mParentMenu)
        {
            SoundManager::GetInstance()->SetVolumeLevel( mSoundLevel );
            mParentMenu->ProcessEvent(InputManager::CANCEL);
        }
    }


protected:
    SoundManager::VOLUME_LEVEL mSoundLevel;
    UIMenu *mParentMenu;

};

class PopLayoutFunction2 : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }

};


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOptionsLayout::UIOptionsLayout()
{
    // Back ground
    UIImage* back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // Creating Generic menu parametrs
    UIMenu *mainMenu = new UIMenu();
    UIMenu *difficultyMenu = new UIMenu();
    UIMenu *soundLevelMenu = new UIMenu();
    Point primaryMenuPoint( 100 ,255 );
    Point secondaryMenuPoint( 430 ,255 );

    // Definging Difficulty Level menu
    difficultyMenu->AddButton("Easy", new SelectDifficultyFunction(1, difficultyMenu) );
    difficultyMenu->AddButton("Medium", new SelectDifficultyFunction(2, difficultyMenu) );
    difficultyMenu->AddButton("Hard", new SelectDifficultyFunction(3, difficultyMenu) );
    difficultyMenu->SetVisibleWhenDisabled(false);
    difficultyMenu->Disable();
    difficultyMenu->SetPos(secondaryMenuPoint);
    difficultyMenu->SetParent(this);
    difficultyMenu->SetCancel(mainMenu);

    // Defining SoundLevel Menu
    soundLevelMenu->AddButton("Very Loud", new SelectSoundLevelFunction( SoundManager::VL_VERY_LOUD, soundLevelMenu));
    soundLevelMenu->AddButton("Loud", new SelectSoundLevelFunction( SoundManager::VL_LOUD, soundLevelMenu));
    soundLevelMenu->AddButton("Moderate", new SelectSoundLevelFunction( SoundManager::VL_MODERATE, soundLevelMenu));
    soundLevelMenu->AddButton("Quiet", new SelectSoundLevelFunction( SoundManager::VL_QUIET, soundLevelMenu));
    soundLevelMenu->AddButton("Mute", new SelectSoundLevelFunction( SoundManager::VL_MUTE, soundLevelMenu));
    soundLevelMenu->SetVisibleWhenDisabled(false);
    soundLevelMenu->Disable();
    soundLevelMenu->SetPos(secondaryMenuPoint);
    soundLevelMenu->SetParent(this);
    soundLevelMenu->SetCancel(mainMenu);
    SoundManager::VOLUME_LEVEL currentVolume = SoundManager::GetInstance()->GetVolumeLevel();
    soundLevelMenu->SetCursorPos( static_cast<int>(currentVolume) );

    // Defining Main Menu
    mainMenu->AddButton("Select Difficulty", new SwitchToFunction(this, difficultyMenu) );
    mainMenu->AddButton("Select Sound Level", new SwitchToFunction(this, soundLevelMenu) );
    mainMenu->AddButton("Done", new PopLayoutFunction2() );
    mainMenu->SetPos(primaryMenuPoint);

    // Add all to renderer queue
    mElements.push_back(mainMenu);
    mElements.push_back(difficultyMenu);
    mElements.push_back(soundLevelMenu);
    mDefaultEventListener = mainMenu;

    mName = "Options";

}// UIOptionsLayout


UIOptionsLayout::~UIOptionsLayout()
{
}// ~UIOptionsLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================


/*void UIOptionsLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PopLayout();
            break;
        default:
            break;
    }

}*/

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
