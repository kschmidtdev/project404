/**
 * An extension of UIElement that represents a single image
 *
 * #include "UIImage.h"
 *
 * An extension of UIElement that represents a single image.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 23 2007    | Added "SetImage" method to dynamically adjust image
 * Karl Schmidt, March 29 2007      | Added correct superclass constructor calling, added alpha and getter/setter for it
 */

#ifndef UIImage_h
#define UIImage_h

// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <UI/UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIImage : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIImage(void);

    /**
     * constructor involving loading bitmap file for image
	 */
    UIImage(const std::string & filename);

    /**
     * Destructor.
	 */
    ~UIImage(void);

// OPERATORS
// OPERATIONS

    void RenderSelf(SDL_Surface* destination);

// ACCESS (writing)

    /**
     * Sets new Image.
	 */
    void SetImage(const std::string & filename);

    void SetAlpha( const unsigned int alpha );

// INQUIRY (reading)

    const unsigned int GetAlpha() const;

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES

    unsigned int mAlpha;
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIImage_h_
