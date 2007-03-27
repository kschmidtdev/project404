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
 * Karl Schmidt, March 27 2007   | Added support for AI difficulty setting/loading
 */
#include "UIOptionsLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>

#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>

#include <SoundManager.h>
#include <GameEngine/GameEngine.h>

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
    SelectDifficultyFunction( const int difficulty, UIMenu* parent )
    : mDifficulty( difficulty ), mParentMenu( parent )
    {
    }

    void operator()(void)
    {
        GameEngine::GetInstance()->SetAIDifficulty( mDifficulty );
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
    SelectSoundLevelFunction( const SoundManager::VOLUME_LEVEL volume, UIMenu* parent)
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
: UILayout(),
  mDifficultyMenu( NULL ),
  mSoundLevelMenu( NULL )
{
    // Back ground
    UIImage* back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // Creating Generic menu parametrs
    UIMenu *mainMenu = new UIMenu();
    mDifficultyMenu = new UIMenu();
    mSoundLevelMenu = new UIMenu();
    Point primaryMenuPoint( 100 ,255 );
    Point secondaryMenuPoint( 430 ,255 );

    // Definging Difficulty Level menu
    mDifficultyMenu->AddButton("Easy", new SelectDifficultyFunction(1, mDifficultyMenu) );
    mDifficultyMenu->AddButton("Hard", new SelectDifficultyFunction(2, mDifficultyMenu) );
    mDifficultyMenu->SetVisibleWhenDisabled(false);
    mDifficultyMenu->Disable();
    mDifficultyMenu->SetPos(secondaryMenuPoint);
    mDifficultyMenu->SetParent(this);
    mDifficultyMenu->SetCancel(mainMenu);

    // Defining SoundLevel Menu
    mSoundLevelMenu->AddButton("Very Loud", new SelectSoundLevelFunction( SoundManager::VL_VERY_LOUD, mSoundLevelMenu));
    mSoundLevelMenu->AddButton("Loud", new SelectSoundLevelFunction( SoundManager::VL_LOUD, mSoundLevelMenu));
    mSoundLevelMenu->AddButton("Moderate", new SelectSoundLevelFunction( SoundManager::VL_MODERATE, mSoundLevelMenu));
    mSoundLevelMenu->AddButton("Quiet", new SelectSoundLevelFunction( SoundManager::VL_QUIET, mSoundLevelMenu));
    mSoundLevelMenu->AddButton("Mute", new SelectSoundLevelFunction( SoundManager::VL_MUTE, mSoundLevelMenu));
    mSoundLevelMenu->SetVisibleWhenDisabled(false);
    mSoundLevelMenu->Disable();
    mSoundLevelMenu->SetPos(secondaryMenuPoint);
    mSoundLevelMenu->SetParent(this);
    mSoundLevelMenu->SetCancel(mainMenu);

    // Defining Main Menu
    mainMenu->AddButton("Select Difficulty", new SwitchToFunction(this, mDifficultyMenu) );
    mainMenu->AddButton("Select Sound Level", new SwitchToFunction(this, mSoundLevelMenu) );
    mainMenu->AddButton("Done", new PopLayoutFunction2() );
    mainMenu->SetPos(primaryMenuPoint);

    // Add all to renderer queue
    mElements.push_back(mainMenu);
    mElements.push_back(mDifficultyMenu);
    mElements.push_back(mSoundLevelMenu);
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

void UIOptionsLayout::OnLoad()
{
    UILayout::OnLoad();

    SoundManager::VOLUME_LEVEL currentVolume = SoundManager::GetInstance()->GetVolumeLevel();
    mSoundLevelMenu->SetCursorPos( static_cast<int>(currentVolume) );
    mDifficultyMenu->SetCursorPos( GameEngine::GetInstance()->GetAIDifficulty() - 1 );
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
