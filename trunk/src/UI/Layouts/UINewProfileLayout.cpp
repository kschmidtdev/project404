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
 * Mike Malyuk,  March 31 2007   | Removed Menu from screen, repositioned Alphabet on screen
 * Karl Schmidt, March 31 2007   | Removed functionality that was moved to UIAlphabetGrid, removed instructional
                                   text that is no longer needed
 * Andrew Osborne, April 5 2007 | Added feedback to alphabetGrid and clearing of text upon loading
 */
#include "UINewProfileLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIImage.h>
#include <UI/UIText.h>
#include <UI/UIManager.h>
#include <UI/UIAlphabetGrid.h>
#include <UI/FuncObj.h>
#include <SecurityManager.h>
#include <Database/DBEngine.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UINewProfileLayout::UINewProfileLayout()
: mAlpha( NULL ), mHelperTxt( NULL )
{
    // Background
    UIImage *back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // AlphabetGrid
    int yStart = 110;
    mAlpha = new UIAlphabetGrid();
    mAlpha->SetPos( Point(90, yStart) );
    mElements.push_back(mAlpha);
    mDefaultEventListener = mAlpha;

    // Add Visual Aid
    int fontSize = 24;
    int fontRed = 255;
    int fontGreen = 255;
    int fontBlue = 255;

	// Not used yet, should be connected with the UIAlphabetGrid eventually to display it's messages
    mHelperTxt = new UIText(" ", fontSize, fontRed, fontGreen, fontBlue);
    mHelperTxt->SetPos( 90, 420 );
    mHelperTxt->SetVisible( false );
    mElements.push_back(mHelperTxt);
    mAlpha->SetMessageText(mHelperTxt);

    mName = "NewProfile";

}// UINewProfileLayout



UINewProfileLayout::~UINewProfileLayout()
{
}// ~UINewProfileLayout


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UINewProfileLayout::OnLoad(void)
{
    UILayout::OnLoad();
    mHelperTxt->SetVisible(false);
    mAlpha->ClearString();
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
