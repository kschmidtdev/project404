/**
 * A one line description of the class.
 *
 * #include "Point.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk,    February 7, 2007 | Initial design
 * Andrew Osborne, February 8, 2007 | Added default construct
 * Mike Malyuk,    February 9, 2007 | Added comparison operator
 * Andrew Osborne, February 10, 2007 | Added set operator that takes both x and y
 * Karl Schmidt,   February 14 2007 | Added consts
 */

#ifndef Point_h
#define Point_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Point
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Point(void);

    /**
     * Constructor
	 */
    Point( const int x, const int y );

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    Point(const Point& from);

    /**
     * Destructor.
	 */
    ~Point(void);
// OPERATORS

    /**
     * Compare points
     */
    bool operator==(const Point &other)const;

    /**
     * Compare points
     */
    bool operator!=(const Point &other)const;

    /**
     * Addition operator
     */
    Point operator+(const Point &other)const;

    /**
     * Integer multiplication operator
     */
    Point operator*(const int &other)const;

// OPERATIONS
// ACCESS (writing)

    /**
     * Set x coord
	 */
    void SetX( const int x );

    /**
     * Set y coord
	 */
    void SetY( const int y );

     /**
     * Set both coordinates in one call
	 */
    void Set( const int x, const int y );


// INQUIRY (reading)
    /**
     * Get x coord
	 */
    int GetX() const;

    /**
     * Get y coord
	 */
    int GetY() const;

protected:
// PROTECTED VARIABLES
    int mX;
    int mY;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Point_h_
