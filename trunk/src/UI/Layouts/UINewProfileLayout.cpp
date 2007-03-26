/**
 * File: UINewProfileLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Andrew Osborne, March 21 2007 | Added AlhpabetGrid to screen
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added true functionality and display (background, menu, instructions)
 * Karl Schmidt, March 23 2007   | Added cast to int to suppress warning
 * Karl Schmidt, March 25 2007   | Added adding checking if a blank username was added, also setting of default password (to be changed)
 */
#include "UINewProfileLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIImage.h>
#include <UI/UIText.h>
#include <UI/UIManager.h>
#include <UI/UIAlphabetGrid.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>
#include <SecurityManager.h>
#include <Database/DBEngine.h>


// Function Objects declaration

class NewProfileDoneFunction : public FuncObj
{

    public:
    NewProfileDoneFunction(UIAlphabetGrid* alpha)
    : mAlpha( alpha )
    {
    }

    virtual ~NewProfileDoneFunction(void) { mAlpha = NULL; }

    virtual void operator()(void)
    {
    	// Don't allow them to proceed if they didn't enter anything
    	// We should really tell them they did something wrong when this occurs
    	if( mAlpha->GetString() == "" || mAlpha->GetString() == " " )
    	{
    		return;
    	}
    	
        if( SecurityManager::GetInstance()->GetUserHash( mAlpha->GetString() ) == "" )
        {
            DBEngine::GetInstance()->SetCurrentProfileName( mAlpha->GetString() );
            SecurityManager::GetInstance()->AddUser( DBEngine::GetInstance()->GetCurrentProfileName(), "rrrr" );
        }

        UIManager::GetInstance()->PopLayout();
        UIManager::GetInstance()->PushLayout("MainMenu");
    }


    protected:
    UIAlphabetGrid* mAlpha;

};

class PopLayoutFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }

};


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UINewProfileLayout::UINewProfileLayout()
: mAlpha( NULL ), mMenu( NULL )
{
    // Background
    UIImage *back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // AlphabetGrid
    int yStart = 110;
    UIAlphabetGrid *mAlpha = new UIAlphabetGrid();
    mAlpha->SetPos( Point(50, yStart) );
    mElements.push_back(mAlpha);
    mDefaultEventListener = mAlpha;

    // Menu
    mMenu = new UIMenu();
    mMenu->SetPos( Point(450, yStart));
    mMenu->AddButton( "Done", new NewProfileDoneFunction(mAlpha) );
    mMenu->AddButton( "Previous Menu", new PopLayoutFunction() );
    mElements.push_back(mMenu);

    // Event Handling
    mAlpha->SetMenu(this, mMenu);
    mMenu->SetParent(this);
    mMenu->SetCancel(mAlpha);

    // Add Visual Aid
    int fontSize = 24;
    int fontRed = 255;
    int fontGreen = 255;
    int fontBlue = 0;
    Point helpStart( 70, 380);
    Point helpOffset(0, static_cast<int>( fontSize*1.2 ) );
    Point p = helpStart;

    UIText* help = new UIText("Press CONFIRM to add letter", fontSize, fontRed, fontGreen, fontBlue);
    help->SetPos(p);
    mElements.push_back(help);
    p = p + helpOffset;

    help = new UIText("Press CANCEL to remove a letter", fontSize, fontRed, fontGreen, fontBlue);
    help->SetPos(p);
    mElements.push_back(help);
    p = p + helpOffset;

    help = new UIText("Press MENU to access the menu on right", fontSize, fontRed, fontGreen, fontBlue);
    help->SetPos(p);
    mElements.push_back(help);
    p = p + helpOffset;

    mName = "NewProfile";

}// UINewProfileLayout



UINewProfileLayout::~UINewProfileLayout()
{
}// ~UINewProfileLayout


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

/*void UINewProfileLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PopLayout();
            UIManager::GetInstance()->PushLayout("MainMenu");
            // Eventually should also push the SetPassword Layout, to update/set password
            break;
        default:
            break;
    }

}*/

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
