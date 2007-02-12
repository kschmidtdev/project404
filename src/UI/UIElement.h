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
     * constructor involving loading bitmap file for image
	 */
    UIElement(const string filename);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    UIElement(const UIElement& from);

    /**
     * Destructor.
	 */
    virtual ~UIElement(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIElement&                     operator=(UIElement& from);

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
    void setVisible(bool nVisible);

    /**
     * Method to set the position of element relative to it's parent
     *
     * @param boolean value true=visible, false=invisible
     *
     */
    virtual void setPos(Point nPos);

// INQUIRY (reading)
    /**
     * Method to see whether the element is visible or not
     *
     * @return boolean value true=visible, false=invisible
     *
     */
    bool getVisible(void);

    /**
     * Method to set the position of element relative to it's parent
     *
     * @param boolean value true=visible, false=invisible
     *
     */
    Point getPos(void);


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
