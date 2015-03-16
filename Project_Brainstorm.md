# A Game #

Since Toby stressed that we should just make a single game instead of a toolkit, we are now making a game. He is also concerned with using a database (ie: making that a significant portion) so we must do a good job of justifying and explaining our use of that component (and the others for good measure).

# Main Components #

Below are the 3 components set out by the project's specifications that must be central to our project. Right now they well contain point-form notes regarding our ideas for each of them.

## UI ##

  * in-game and game frontend widgets and layouts
  * in-engine map editor?

_Unsure whether the map editor will be incl with the product (if we make it good I don't see why not) but we definitely will need one once we get past the single stage point, and need to design multiple. Likely will need to include the setting of variables associated with that square._

_In addition we need to decide what feel we want for the tiles. Should they have height, should it be represented, from what perspective etc. --Mike
## Database ##_

  * templates for characters, items, enemies
  * instantiations of templates, ie: a particular enemy that has it's own amount of HP/MP left
  * could function as hub of all game data, allowing use as a game save/load system

_Just to elaborate on the DB idea. The templates will most likely hold the range of values where an item can be given (think diablo2 style where weapons had a set max and min but were generated within those frames). Additionally templates will allow us to segregate content so that level 20 weapons aren't given to level 1 characters etc._

_The instantiation portion would be like a separate part of the database dealing solely with items/characters/whatever that is actually in the game environment at any given time.
-- Mike_

## Security ##

  * password-protected + encrypted user profiles (where their own savegames could live)
  * encryption/decryption services for game data, in particular the game database

# Technical Issues #

## 2D or 3D? ##
Karl:
Mike and I talked about this earlier on today and we both feel that we should focus on 2D first, since all the gameplay and UI should operate in a 2D space, but keep the design open to allow for another (OGRE) rendering method where we could view the world in 3D.

We are supposed to make 3 versions of our project, so if we stick with 2D only for the first version we will have a better idea how feasible 3D is, and then add that in during V2 or V3.

Mike: Agrees. I think we definitely want this off the ground first. If designed properly, the gui 2D 3D world should be making calls to the main game, which will do all the real work behind the scenes. This would be the ideal situation, but I say first we make sure we have something working as v1 is important to have.

## Libraries ##
Karl:
I think for our 2D renderer and input system we should use [SDL](http://www.libsdl.org). It's cross-platform and pretty easy to use.






