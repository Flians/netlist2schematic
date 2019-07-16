#ifndef DIRECTION_H
#define DIRECTION_H

namespace ns {

enum class Direction{
    /** undefined layout direction. */
    UNDEFINED,
    /** rightward horizontal layout. */
    RIGHT,
    /** leftward horizontal layout. */
    LEFT,
    /** downward vertical layout. */
    DOWN,
    /** upward vertical layout. */
    UP
};

}
#endif // DIRECTION_H
