## Introduction ##

Post your ideas below following the format outlined.

## Example Project Idea Name ##
  * **Type:** Game, business application, etc
  * **UI Component:** Briefly describe what the UI component would do
  * **Database Component:** Briefly describe what the DB component would do
  * **Security Component:** Briefly describe what the security component would do
  * **Description:** Give a brief overview of what the project is. Include information like resource requirements (ie: art, sound, design) and potential library requirements (OpenGL, SDL, etc)

Simply copy and paste the markup above to use as a template for your contributions.

# Actual Ideas List: #

## 2D Tile-based Game Creation Kit ##
  * **Type:** Game toolkit
  * **UI Component:** A 2D renderer for the actual game, and a tile-based map editor combined with a database-like property editor
  * **Database Component:** A database that stores game data like text (names of things, text that is displayed), game data (hit points of things, speed of things, map layout, etc), texture data (sprites, tiles, etc), possibly audio data, and game state data (current state of all entities)
  * **Security Component:** Not 100% sure what this could be, but it could be to ensure the integrity of the database, and also fully encrypt and decrypt it, could also contain a secure game profile system (password protected game profiles to store save information, etc)
  * **Description:** Basically a toolkit that comes with libraries we will write, and a map/property editor GUI tool that can all be used to quickly build simple->complex 2D tile-based games with. We could supply small game games as tests/demonstrations of our toolkit, so art requirements should be light. I suggest with use the SDL library (if we are allowed) to do all the rendering, image format loading and input for us (we still have to manage and do something intelligent with it).

# More Details #

OK so it seems like the Game Creation Kit idea is the one we want to go with. We should start outlining more details and moving towards exactly what our toolkit will do, and what it won't do.

  * Contain a map editor (can be basic)
    * this could be done with the win32 API, MFC, but preferably rendered with a GUI lib we could write within our renderer or something like wxPython (python extensions to a windowing library)
  * Does not 'make' a game
    * Basically gives a skeleton application and libraries that can be used to make a game, but doesn't have a 'make this type of game' button
  * Does not depend on a specific renderer
    * We need to outline a generic interface to renderers, so we could have a 2D SDL-based renderer (for Windows/Linux/EvenMac, and even GP2x :) ) as well as a 3D renderer using OpenGL or OGRE
  * We may not include the actual renderers in the scope of the project, just the generic interface
    * This could mitigate issues with using external libraries, but could also add more non-CMPT275-specific workload

Feel free to comment/change/add to this list! Please! :)
