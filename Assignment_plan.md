Current assignment todo list

# Presentation #

So we will need to figure out who wants to talk about what for our short presentation on friday. Here is a list of things that need to be talked about:

  * Show the website
  * Show the risk table
  * Talk about our database component and how it would work
  * Talk about our project description

1. Overview by MIKE

2. User Interface by ANDY

3. Database by KARL

4. Security by HAN

> One of the possible threats to our game system is unauthorized user gains direct access to the game’s save file (or profile) and corrupt the data by arbitrary editing. Consequently, this kind of threat can make the game runs improperly, even can bring the unpredictable termination. To prevent this, we will add simple, but a stand alone security component to our game system.
> The security component mainly will handle the data encryption and decryption. For instance, we convert the save data to some sort of encrypted binary data when saving is performed during the game and decrypts a binary-based save file when loading the game data.
> Another major role of the security system is protecting user profiles in the game by password. This is very common way of security but also useful enough for this performance. Since we plan to have two input devices—keyboard and joystick, we will have a similar password-input-interface like XBOX360 Live Login which can be suitable for both keyboard and joystick.

# Assignment 1: Project Plan and Website #

_.... so we haven't 'finished' a lot...._

  1. Design your project website. Include the following information:
    * Team name. _done_
    * Full name, student #, and email address of each team member. _Emailed Toby about the student # thing, he replied almost right away back saying we can just list the full names + email addresses_
    * A list of three 1-hour time slots during the week when your entire team is able to meet on the Surrey campus. We may use these times to schedule meetings with instructors/TAs. _done, see calendar_
    * The project manager (PM) for this assignment. The PM is responsible for organizing meetings, recording and distributing meeting minutes, and any other administrative tasks that need to be taken care of (such as submitting assignments!). Your team will need to decide who the PM will be for each assignment. _Assignment 1 PM - Karl_
    * A clear indication for which assignment this is being submitted, i.e. put "Assignment #1: Project Plan and Website" in big letters at the top of the page. For future assignments, replace this with the name of that assignment.
    * A table of contents linking to the 5 assignments. You don't need any content yet, but you should provide templates and "stubs" for all the content.
    * Write a project description. Describe your project in a way that a non-CS SFU student would understand. Briefly mention the main features you plan to implement. Pretend you are trying to get users interested in using your system.

> The website must be easy to read and navigate.

> 2. Make a team schedule. Create a detailed schedule over the semester that shows all the times when your team will meet, when it can and meet, and when it can't meet. Take into account known absences of team members, holidays, etc. Be sure to note all the due dates of all assignments and exams for the course.

> 3. Version control. Provide the URL for your team's SVN repository. Also provide instructions for how someone can checkout your project. _[here](http://code.google.com/p/project404/source)_

> 4. Create a risk table. In a table like the one shown, state each risk clearly, including its likelihood (e.g. low, medium, high chance) and severity (e.g. low, medium, high, catastrophic). For each risk, describe what you will do to prevent it, and what you will do if it actually happens. Think hard about these and choose relevant risks --- thinking about potential problems ahead of time can be can save you a lot of pain later!


## Comments ##

_Well this isn't necessarily a difficult assignment but we really need to have a meeting when all team members are on site. I know there is a lot of grumbling about getting up and meeting before class, but until we have a meeting and can figure out times that are good for everyone, I might suggest we do the only thing we can and get it over with. Likely we could finish this off in a short period of time after we get an initial face to face meeting. Just my thought -- Mike_



# Project Description #

Team 404’s Project will be a 2D turn-based (grid-based) strategic game. Our goal is to create a strategy game derived from the style of games that came before it such as Final Fantasy Tactics, Fire Emblem, Super Robot Wars and Advance Wars. The main objective of our game is to have the user utilize unique units and weapons to defeat an enemy composed of similar units during instanced combat. These loose instances of combat will be tied into the overarching storyline through a world map, where players will choose which conflicts they wish to participate in. The technical aspects of our game will be designed with modularity in mind. The 3 main aspects of our game will revolve around the user interface, the database and the security.

The user interface will be defined mostly through menus, with the primary input being keyboard, and possibly game pad. Additionally the UI will display information regarding the various important information regarding the battlefield and battle-related information (units, land etc.). We hope by providing a modular design between the UI and the security and database components of the product, that given extra time, we can create additional modes of replay, including possible 3D integration, or porting to portable systems.

The database driving the production of this game will be largely involved in tracking and distributing information pertaining to units, weapons, and text. The database will utilize templates of weaponry to generate instances of all game objects during play.  This database will support item and text look up because the game will need to randomly generate items (so we cannot point to a direct item in the database for templates). Additionally it will control instances of existing objects in the game for tracking and access purposes. The database will be effective because of the large amount of content (generally many weapons, characters, in game text, and/or images and media) being stored, and the need to have an organized and accessible central information store.

Lastly the security of our game will be supported both through profiles (a method of user permission management), which will be locked user profiles that maintain integrity of player’s games and through basic encryption of files and game data to maintain integrity of file state. This will be used to prevent players from circumventing the systems in play, and force these players to “play fair”.

Overall, our goal is to create an engaging and thought provoking game that will force users to play an active mental role in the action on screen. Our game will be a strong display of proper programming practices in modularity, and display key understandings in the underlying aspects of good software design.

_Added changes based on Andrew's suggestions, may want to add further info after our meeting._

# Risk Table #
pg 106-110

Values for Likelyhood are: Very Low (< 10%), Low (10-25%), Moderate (25-50%), High (50-75%) or Very High (>75%)

Values for Impact are: Catastrophic, Serious, Tolerable or Insignificant

| **Risk** | **Likelyhood** | **Impact** | **Preventative Measures** | **If it happens** |
|:---------|:---------------|:-----------|:--------------------------|:------------------|
| A member becomes ill or is unable to fulfill their duties | Low | Serious | Not much can be done about someone becoming sick, best to keep members posted on your condition and work | The remaining members of the team should come together to divvy up the sick/missing teammates work |
| Project gets behind schedule | Moderate | Tolerable | Keep calendars of events, set milestones, make sure all members know when their work is due | Make a plan to get the team back on track. Set incentives and ensure all members are utilizing their time wisely. |
| Project is "refactored" by Teacher or TA | Low | Serious | Keep in touch with TA and Teacher about their thoughts on the current project. Make sure to not try anything too drastic and time consuming before ensuring they believe it necessary or contributes towards the end goal of the project. | Quickly fix the issue at hand, and ensure that the correct information or plan is acted upon immediately with Teacher or TA's comments guiding this plan. |
| Teammate is constantly missing, shows no interest in work | Very Low | Serious | Make sure to keep in touch with team at regular intervals. Try to keep track of each team member's progress. | Try to push the team mate back to work. See if there are any issues outstanding that may be causing them to become lax on the project work. Try to work towards a solution with them. If to no avail, consult the Teacher or TA about the matter |
| Project hardware/software requirements outpace the computers at school | Low | Serious | Try to keep code relatively optimized. Additionally, make sure to consistently test the product so these problems can be caught relatively early | Try and debug the code, cutting out pieces until the culprit can be found. Maybe assign one member to find the slowdown |
| Project Goals are too ambitious for project | Moderate | Serious | Communicate with team members and teacher/TA regularly | Cut non-essential features when required, refactor essential features if required |
| There is a personal conflict among project members | Low | Serious| Decent communication with other team members within/without the the project. No extreme self opinion.| Talk to the member with mutual understanding to each other's opinion. |
| There is a discrepency between compiler configurations and errors occur upon collaboration | Low | Serious | Run preliminary tests on all four home machines to ensure that all the necessary components required for our software compile properly | Find the home computer(s) that are missing compiler options, correct them and adjust any code as required |
| There is a discrepency between perceived objectives/assigned-tasks and those that were completed | Moderate | Serious | Before conclusion of a meeting in which tasks are assigned, each group member must explain what his task is and what task the code he will write should perform | The task is re-assigned (possibly to the same person) to correct the code (or assignment) so that it performs the originally desired function.  |
| One does more works than others. | High | Tolerable | We should know the exact capability of each team member previous to the actual assignments. | Rediscuss & Redistribute the amount of works to each team member in more fair way. |



Security:

| Users and permission management | User profiles, only  have access to 'their' savegames (pwd protected) | System for verifying a 'secur' password? i.e. check user pwd against dictionary |
|:--------------------------------|:----------------------------------------------------------------------|:--------------------------------------------------------------------------------|
| 'Integrity' check/security | Encryption + Decryption of game data + save games | pwd can be a keyboard-entered word/text or recorded joystick buttons/directions |