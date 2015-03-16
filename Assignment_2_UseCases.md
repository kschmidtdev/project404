# Functional Requirements #

## List of Actors ##

### Veteran Gamer ###

Name: Max H. Pearson

Profile:  Max has always been a fan of the ultimate in tactics games. Having played them all, from fire emblem to final fantasy tactics, Max loves tactics. He's the kind of guy that will put his archers on a hill to gain that extra space of damage. When Max isn't in his latest battle, he is talking with his friends about the strength of his units and their specialties. Generally, Max says he enjoys the plot as much as anyone else, but what it boils down to for him, is careful planning, and quick decisive moves with little room for error. This kind of play makes Max apt to go with his strongest characters, seek out the best items, and generally specialize his characters to the maximum of their ability.

Goals:
  * Generally wants to gain the most in physical terms (most characters, most weapons)
  * Loves unique and powerful weapons/characters
  * Is willing to seek out unique game play opportunities
  * Wants to crush the enemy AI

Abilities:
  * Good grasp of Tactics style games
  * Strong incentive to complete all goals and tasks
  * Relatively strong interpretation ability
  * Willingness to quickly identify information that will strengthen his game.


### "Newbie" Gamer ###

Name: Hubert Nuburton

Profile: Hubert is new to tactics. Lately his friends have all been playing tactics games, and he wants to give it a shot. However, Hubert's friends are usually busy doing their school work, so Hubert has to learn on the fly. Although he has never tried tactics before, he believes that this type of game can't be that hard to learn. He just wants to play the game, and although he won't learn as much by doing so, he wants the accomplishment of getting through it on his own. At least that way he can gain the key to communication with his peers, and be on equal footing.

Goals:
  * To finish the game
  * To learn tactics style games on his own
  * To have something to say to his friends

Abilities:
  * Highly Enthusiastic
  * Willingness to learn (short attention span)
  * Not afraid to try something new

## Short list of Use Cases ##

Attacking/Moving: ALL

Entering Text: ALL

Load Profile: ALL

New Profile: ALL

Status: Hardcore

Item Buying: Not Newbie

Equipping: Not Newbie

Setting Options: ALL

Save (from Map): ALL

Load (from Map): ALL

New Game: ALL

Quitting (from Map): ALL

Party Options: Not Newbie

Main Map: ALL

## Use Case Map ##

![http://www.sfu.ca/~mmalyuk/275/Flow.png](http://www.sfu.ca/~mmalyuk/275/Flow.png)

# FINAL #
Overview: This scenario will cover the basics of playing the game

**Name:** Name and Password

**Description:** The user must enter a name and password when creating a profile.

**Actors:** ALL

**Use Case:**

###  ###

Normal:

1. Type:  Characters into text field

Alternative:

1. Joypad: To select characters

2. Selection: “Ok” when finished, text affirms decision with yes or no.

3. Affirmation: User selects Yes, if no, go to 1.

Abnormal:

2 ii) Erasing: User uses backspacing or selects backspacing to remove characters.

**Features Used:**
  * Selection Cursor
  * Text box
  * Button (affirmation yes or no, and ok)
**Exceptions:**
  * If the user does not enter a name, the screen will respond with a message to the user, indicating they should.

**Actors:**

_Max:_
Max doesn't necessarily mind making a new profile, because he wants to know exactly how well he does in the game. As long as he can view the time he has played the game for, and the stats he has attained in doing so, profiles are always a good idea.

_Hubert:_
Hubert isn't exactly sure why he is required to use a profile, but since he wants to get to the game, he is willing to get one started. At least he'll know he isn't spending too much time on games.

**Screen Mockups:**

###  ###
**Name:** Load Profile

**Description:** The user loads a previously saved profile

**Actors:** ALL

**Use Case:**

###  ###

Ordinary:

1. Selection: Move the cursor to “Load Profile”

2. Selection: Move cursor over player profile with user's name

3. Text Entry: Write password in password box

Abnormal 1:

1. Selection: Move the cursor to “Load Profile”

2. Selection: Move cursor over player profile with user's name

3. Text Entry: Write password in password box

4. Wrong Entry: User is notified, writes again

Abnormal 2:

1. Selection: Move the cursor to “Load Profile”

2. Selection: Move cursor over player profile with user's name

3. Selection: Select Cancel, if the user selects incorrect profile

4. Text Entry: Write password in password box

**Features Used:**
  * Selection Cursor
  * Menu
  * Button
  * Profiles
  * Saving/Loading

**Exceptions:**
  * Incorrect password entry, rectified by allowing the user to enter again
  * Incorrect selection of profile, rectified by allowing the user to “cancel” entry.

**Actors:**

_Max:_
Loading the profile is essential for tracking his latest feats. Max is keen to do so.

_Hubert:_
Hubert knows he has to use his profile to play the game, so loading it is a necessity.

**Screen Mockups:**

###  ###

**Name:** Main Options

**Description:** The user accesses the Options Menu (before game)

**Actors:** ALL

**Use Case:**

###  ###

Ordinary:

1. Selection: Move the cursor to Options and enter

2. Selection: Select volume bar, move to left for less or right for more.

3. Validate: Select Apply Changes.

Abnormal 1:

1. Selection: Move the cursor to Options and enter

2. Selection: Select volume bar, move to left for less or right for more.

3. Reset: User makes an error, selects “use defaults”

**Features Used:**

  * Selection Cursor
  * Menu
  * Button
**Exceptions:**

  * Incorrect volume, allow user to reset to defaults

**Actors:**

_Max:_
Max doesn't care about the volume in game, heck he has speakers. He supposes if the AI became an option he'd find this more useful, but at the moment it seems frivolous at best

_Hubert:_
Hubert doesn't like to multi task. Generally if he is focusing on something new he gives it his full attention. Thus including the volume and other options at this level suits him just fine.

**Screen Mockups:**

###  ###

**Name:** Start a New Game

**Description:** The user must start a new instance of the game.

**Actors:** ALL

**Use Case:**

###  ###

Normal:

1. Selection: Move the cursor to “New Game”

2. Start: Use enter to start the game.

**Features Used:**

  * Selection Cursor

  * Menu

  * Button

**Exceptions:**

> N/A

**Actors:**

_ALL_:
Understand this is important to get started.

**Screen Mockups:**

###  ###

**Name:** Playing Tutorial

**Description:** The user must start the tutorial mode

**Actors:** Hubert

**Use Case:**

###  ###

1. Selection: Move the cursor to “Tutorial”

2. Start: Use enter to start the tutorial.

**Features Used:**

  * Selection Cursor
  * Menu
  * Button
**Exceptions:**

> N/A

**Actor:**

_Max:_
Max doesn't despise tutorials, but since he is familiar with the tactics games, he feels that utilizing a boring, long tutorial will not benefit him. Frankly it prevents him from getting his characters up to snuff fast enough. He would much rather get started right away, so he choose to not do the tutorial

_Hubert:_
Hubert isn't exactly sure why he is required to use a profile, but since he wants to get to the game, he is willing to get one started. At least he'll know he isn't spending too much time on games.

**Screen Mockups:**

###  ###

**Name:** Load Game

**Description:** The user selects their saved game

**Actors:** ALL

**Use Case:**

###  ###

Ordinary:

1. Selection: Move the cursor to Load game and Enter

2. Selection: Select preferred saved game.

3. Validate: User accepts when asked if this is the game they wish to load

Abnormal 1:

1. Selection: Move the cursor to Load game and Enter

2. Selection: Select preferred saved game.

3. Validate: User denies when asked if this is the game they wish to load

4. Selection: User is returned to load menu, and may select again.

**Features Used:**

  * Selection Cursor
  * Menu
  * Button
  * Loading

**Exceptions:**

  * Incorrect save game, allow user to go back before finalizing choice

**Actor:**

_All:_
They all know that to load a game is imperative to playing the game.

**Screen Mockups:**

###  ###


**Name:** Navigating the World Map

**Description:** The user must navigate a map, and enter an item shop (marketplace/armory)

**Actors:** ALL

**Use Case:**

###  ###

1. Selection: Move the cursor to toward a city

2. Movement: By selecting the node, the character will move to this point

3. Menu: Press the menu button to bring up the menu.

4. Selection: Navigate menu to "Armoury/Marketplace"(whichever is there) and enter.

Abnormal:

1. Selection: User selects node that does not contain a city

2. Movement: Player moves to position

3. Menu: Pressing the menu button brings up the menu.

4. Unselectable: Menu does not allow selection of Armoury or Marketplace.

5. Movement: Player moves until they are on a city.

Abnormal 2:

1. Selection. User selects an area on the map where no nodes or roads exist

2. Movement: No movement occurs until a valid movement is proposed.

**Features Used:**

  * Selection Cursor
  * Button
  * Menu
  * World Map
  * Movement

**Exceptions:**

  * Choosing the wrong position (movement but no marketplace or armoury present or selectable)
  * Choosing an invalid position (no movement)

**Actor:**

_Max:_
Max is in his element here. He is unlikely to make mistakes as almost every tactics game he has played used some variation of a world map to link battles together. After some quick tinkering, he knows how the navigation works, and correctly assumes that cities will contain armories and marketplaces, because no one can get items from a blank node! Since the maps are relatively well laid out, he can quickly glean the information he needs to effectively utilize the map.

_Hubert:_
Hubert is quickly overwhelmed by the situation at hand. Relying on the tutorial, Hubert tentatively navigates around the map, but definitely isn't sure of himself. It is obvious that there are cities and blank nodes, but he doesn't necessarily link their relation to marketplaces/armories. He spends more time on this level, and is more likely to make errors, but he too will learn quickly as there are few ways to make mistakes with linear pathing. At the very least, he does recognize the need for the map, but does have difficulty with it.

**Screen Mockups:**

###  ###


**Name:** Using Marketplace

**Description:** The user must utilize the menu list to buy items for their units.

**Actors:** ALL

**Use Case:**

###  ###

1. Selection: Move the cursor to select the type of weapon/spell/armor needed (Sword/Axe/Shield/Spell etc.)

2. Selection: Press the selection button on desired object.

3. Selection: Affirm selection with another button press. (item placed in repository)

4. Exit: Select exit option, press button.

Alternate:

1. Selection: Move the cursor to sell and select

2. Selection: Select the item from your repository with button press.

3. Selection: Affirm selection with another button press. (item removed from repository money given back)

Abnormal 1:

1. Selection: User selects an item they cannot afford (greyed out)

2. Selection: Game informs user, item is too expensive. Must select again.

**Features Used:**

  * Selection Cursor
  * Button
  * Menu
  * Database (storage)

**Exceptions:**

  * Choosing the wrong item (error message generated)

**Actor:**

_Max:_
The marketplace is both intuitive and simple to Max. Judging from the amount of coin he has, and the items available, Max is able to view their statistics and decide which would benefit his units the most.

_Hubert:_
Hubert will have trouble understanding the use of the marketplace. Since he has little knowledge of statistics and weapon stats, he will find it confusing and difficult to decide which weapons he should and should not buy. Additionally he does not understand (at least at first) which classes use what weapons, nor how to gain and use money, so utilizing the marketplace/armory early on will be difficult. However, the marketplace is not necessarily needed, since items can appear in game, so the marketplace may not be required to him.

**Screen Mockups:**

###  ###

**Name:** Accessing party status

**Description:** The user must navigate the world map menu to access party status.

**Actors:** ALL

**Use Case:**

###  ###

1. Selection: Press the menu button to bring up the menu

2. Selection: Navigate to the "Party Status" button, and press the button.

Abnormal:

1. Selection: User selects menu item that is not Party Status

2. Selection: Select back or cancel, and go back to menu. Try again.

**Features Used:**

  * Selection Cursor
  * Button
  * Menu
  * Database (unit modified)

**Exceptions:**

  * Choosing the wrong option (go back and try again)

**Actor:**

_Max:_
Ah the party status screen. Max's bread and butter. Max loves to set up his characters and their abilities as best as possible, so to Max this option is the holy grail of tactics games. He is likely to spend much time in here, pouring over stats and setting up parties, as such he knows how to access it easily.

_Hubert:_
The party status screen is definitely infinitely more difficult for Hubert than for Max. Hubert doesn't want to have to learn these things, and is quickly overwhelmed by the options available to him here.

**Screen Mockups:**

###  ###

**Name:** Party Status

**Description:** The user must be able to set their starting member roster, and equip their units with items.

**Actors:** ALL

**Use Case:**

###  ###

Case Party Setup:

1. Selection: Move the cursor onto a unit and press button

2. Selection: In sub menu, select option (Include in party)

Abnormal:

1. Selection: User selects too many to be in party

2. Selection: User receives warning message, that too many members are in party, to either de-select a member or not add a new one.

3. Selection: Do nothing if not adding, otherwise, select a character that is in party (noted by highlight) and press button.

4. Selection: In sub menu, select option (remove from party).
  * _Note if the user tries to remove all members from party a similar warning will be produced to warn them_

Case Unit Item Selection:

1. Selection: Move the cursor onto a unit and press button

2. Selection: In sub menu, select option (Set Items)

3. Selection: From items menu, select the item you wish to change (from the unit), with the item you wish to use (from the repository).

**Features Used:**

  * Selection Cursor
  * Menu
  * Items
  * Button
  * Units
  * Database

**Exceptions:**

  * Choosing too many or too few party members (error message generated)

**Actor:**

_Max:_
Max will spend many a meticulous hour working through his party status, and realizing his true dream team. It is imperative for him to be able to glean as much information as possible from the content. He wants a simplified interface, yet lots of information. Additionally he needs the to use the items

_Hubert:_
Hubert will need to use the party screen to set up his party, but he really wants to avoid the other work. Although he may set parties, he is unlikely to spend much time comparing stats and items. He would prefer a simple intuitive way to do this, without being bogged down by heavy text and stats.

**Screen Mockups:**

###  ###

**Name:** Entering Battle

**Description:** The user must navigate a map, and join (move to) a conflict denoted by a red mark.

**Actors:** ALL

**Use Case:**

###  ###

1. Selection: Move the cursor to toward the contested point

2. Movement: By selecting the node, the character will move to this point

Abnormal:

1. Selection: User selects node that is not contested

2. Movement: No action results, user continues movement

3. Arrival: When arriving at the correct node, the instance will start.

Abnormal 2:

1. Selection: User selects an area on the map where no nodes or roads exist

2. Movement: No movement occurs until a valid movement is proposed.

**Features Used:**

  * Selection Cursor
  * Movement

**Exceptions:**

  * Choosing the wrong position (movement but no instance)
  * Choosing an invalid position (no movement and no instance)

**Actor:**

_Max:_
Max knows what an instance of battle is, and he knows how to join them. It's necessary and he's ready to go.

_Hubert:_
Hubert doesn't really understand how the battles work, but he knows where a action instance is, by the large red marker on the screen. He knows that there has to be a battle somewhere so he knows where to go.

**Screen Mockups:**

###  ###

**Name:** In Game Status

**Description:** The user must enter the in Game Status menu(battlefield), view current statistics of units

**Actors:** ALL

**Use Case:**

###  ###

1. Selection: Press the select button

2. Selection: Side menu shows listing of all characters on field with basic info. Selecting a unit brings up submenu.

3. Selection: Submenu displays further information, button press exits menu


**Features Used:**

  * Selection Cursor
  * Menu (s button)
  * Button
**Exceptions:**

> N/A

**Actor:**

_Max:_
To Max the in game status is imperative to his analysis of the current in game situation. By having it easily mapped to a single button, Max can quickly scan his team's statistics, and, if needed, get more in depth information at the click of a button. He is likely to utilize this menu extensively while planning his next move.

_Hubert:_
Hubert has never really needed to know too much about his units. Knowing their basic health and power was usually enough to satiate his need for tactical play. He generally prefers to use the big and powerful looking characters, and finds stats to be boring. At least the stats menu isn't obtrusive to his game play.

**Screen Mockups:**

###  ###

**Name:** Moving

**Description:** The user must navigate the tactical map, aided by the tutorial mechanism

**Actors:** ALL

**Use Case:**

###  ###

Ordinary Usage:

1. Selection: Select an allied character

2. Movement: Move the cursor within the movement range of the character (denoted by bordered box)

3. Commit: Use the action button to move the unit to the spot at the cursor.

Abnormal 1:

1. Selection: Selecting ground

2. Selection: User cannot select ground, only allowed to select unit

Abnormal 2:

1. Selection: Select an allied character.

2. Movement: Move character outside the allowable movement area (not allowed).

**Features Used:**

  * Selection Cursor
  * Button
  * Tiles

**Exceptions:**

  * Selecting ground (no effect)
  * Trying to move to invalid position (restricted to movement area of unit only)

**Actor:**

_Max:_
Max understands the basic mechanics of movement, and really only wants to know where his units can and cannot move to. By allowing him to view the area of movement, Max is able to better plan his attack.

_Hubert:_
Hubert may not be able to easily understand the movement pane, but he finds it useful because it restricts his cursor only to squares he can legitimately move to.

**Screen Mockups:**

###  ###

**Short Name:** Attacking

**Informal Description:** During the course of the game, the user will have to be able to get their character into a position where they may attack an opponent character.

**Actors:** ALL

**Use Cases:**

###  ###

_Casual Gamer:_

1. Selection: Player selects his/her own unit

2. Choose Target: Player uses cursor and places it over opponent before accepting.

3. Selects Weapon: Player navigates menu, selects appropriate weapon.

4. Attacks: Player affirms attack action.

###  ###

_"Hardcore" Gamer:_

1. Check Skills: Player checks character statistics before choosing target.

2. Check Opponent Skills: Player checks opponent statistics by placing cursor over opposing character.

3. Selection: Deciding it is a good move, player selects his/her own character.

4. Choose Target: Selects character he/she planned to attack with cursor.

5. Selects Weapon: Player navigates menu, selects appropriate weapon.

6. Attacks: Player affirms attack action.

###  ###

_"Newbie" Gamer_:

Ordinary:

1. Selection: Player selects his/her own unit

2. Choose Target: Player uses cursor and places it over opponent before accepting.

3. Selects Weapon: Player navigates menu, selects appropriate weapon.

4. Attacks: Player affirms attack action.

Abnormal 1:

1. Selection: Player selects a unit not their own

2. Re-Selection: Interface does not allow selection of opposing units, player reselects

3-5 Continue as normal

Abnormal 2:

1. Selection: Player selects his/her own unit

2. Choose Target: Player uses cursor and places it over ally or blank ground.

Stem:

3i: Player has selected ground, this will only be allowed if attack is Area of Effect (attack damages more than one space, and may still be effective)

3ii: Player has selected ally, attack will only be allowed if "healing".

4-5 Continue as normal

###  ###

**Features Used:**

  * Cursor (and associated controls)
  * Selection button
  * Information button
  * Details menu
  * Weapons menu
  * Weapon/Spell

**Exceptions:**
  * If a user selects the wrong unit or a unit who has already had it's turn, the game will not allow selection.
  * If a user tries to attack an ally, it will only be allowed if a healing ability if invalid, will wait until user selects proper target
  * If a user tries to attack ground, it will only be allowed for an area of effect attack if invalid, will wait until user selects proper target
  * Unusable weapons for selection will be greyed out, and attempts to use these weapons will not be allowed, waits for proper input.

**Actor:**

_Max:_
To Max this is all second nature. Using area of effect spells is something common in most tactics games, and in fact, using them on open ground does have benefits, including avoiding his own units, or hitting more of the opponents units. Although he may need to figure out which ways to best utilize this ability, he is likely to understand the gist of the games attack mechanics easily and early on.

_Hubert:_
Hubert finds the attack mechanics confusing. How come his archer can only attack units while his mage can hit open ground. He feels that the system allows him to make more errors than it should. Although generally manageable, he does require more guidance in this area to effectively utilize the attacking mechanic.

**Screen Mockup**

###  ###

**Name:** Saving

**Description:** Once the battle has ended, the user must save from the overmap

**Actors:** ALL

**Use Case:**

###  ###

Ordinary Usage:

1. Menu: Access the menu by pressing the menu button

2. Selection: Select the save option

3. Selection: In the save menu select an empty space.

Abnormal Usage:

1. Menu: Access the menu by pressing the menu button

2. Selection: Select the save option

3. Selection: Select already in use save slot

4. Input: Answer with button on Yes overwrite or No do not.

Abnormal Usage 2:

1. Menu. Access the menu by pressing the menu button

2. Selection: Select improper action.

3. Selection: Choose cancel and go back to main menu.

4. Selection: Select proper option.

5. Selection: In the save menu select an empty space.

###  ###

**Features Used:**

  * Selection Cursor
  * Action button
  * World Map Menu
**Exceptions:**

  * Selecting improper button (simply go back and choose correct)
  * Overwriting files (ask if they are sure)

**Actor:**

_Max:_
Max knows and utilizes saving as a given.

_Hubert:_
Hubert will know to save, but he may need to learn how to reach the save menus so as to use them.

**Screen Mockups:**

###  ###

**Name:** Quitting

**Description:** The user wishes to exit the game from the main map

**Actors:** ALL

**Use Case:**

###  ###

Ordinary Usage:

1. Menu: Press menu button to access the menu.

2. Selection: Select the quit option.

3. Selection: Select Yes when asked if they are sure.

Abnormal Usage:

1. Menu: Press menu button to access the menu.

2. Selection: Select the quit option.

3. Mistake: Select No to go back to game.

###  ###

**Features Used:**

  * Selection Cursor
  * Action button
  * World Map menu

**Exceptions:**

  * Selecting No, back to map

**Actor:**

_All:_

Quitting is intuitive and imperative in operation for both users. Since it is easily identifiable on the menus, it should be simple to apply.

**Screen Mockups:**

###  ###