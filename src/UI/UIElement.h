/**
 * Base (abstract) class that represents a single element on the screen
 *
 * #include "UIElement.h"
 *
 * Elements include buttons, menus, the battle grid, labels, text, images, etc.
 *
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 7 2007 | Initial Design
 * Andrew Osborne, February 10 2007 | added bitmap constructor, added RSM and rend variable
 * Andrew Osborne, February 10 2007 | Added more documentation, removed RSM/rend
 * Karl Schmidt, February 12 2007 | Removed unnecessary copy constructor and assignment operator overload
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 */


#ifndef UIElement_h
#define UIElement_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Renderer/SDLRenderable.h>
#include <Renderer/SDLRenderer.h>
#include <ResourceManager/ResourceManager.h>
#include <Point.h>


// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIElement : public SDLRenderable
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIElement(void);

    /**
     * Destructor.
	 */
    virtual ~UIElement(void);

// OPERATORS
// OPERATIONS
    /**
     * Method to Draw the element on the screen
     *
     * @param Desitination surface
     *
     */
    virtual void RenderSelf( SDL_Surface* destination);

// ACCESS (writing)
    /**
     * Method to set whether the element is visible on the screen or not
     *
     * @param boolean value true=visible, false=invisible
     *
     */
    void SetVisible( const bool nVisible );

    /**
     * Method to set the position of element relative to it's parent
     *
     * @param Point data type
     *
     */
    virtual void SetPos( const Point & nPos );

    /**
     * Method to set the position of element relative to it's parent
     *
     * @param x - x value, y - y value
     *
     */
    virtual void SetPos( const int x, const int y );

// INQUIRY (reading)
    /**
     * Method to see whether the element is visible or not
     *
     * @return boolean value true=visible, false=invisible
     *
     */
    bool GetVisible(void) const;

    /**
     * Method to set the position of element relative to it's parent
     *
     * @param boolean value true=visible, false=invisible
     *
     */
    Point GetPos(void);

    /**
     * Method to examine element image
     *
     * @return boolean value true=visible, false=invisible
     *
     */
    SDL_Surface* GetElement(void);

protected:
// PROTECTED VARIABLES
    bool mVisible;
    Point mPos;
    SDL_Surface* mElementImage;



private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIElement_h_
