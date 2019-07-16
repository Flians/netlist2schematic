#include "include/graph/side.h"
#include "include/graph/direction.h"

namespace ns {

/**
        * Returns the next side in clockwise order.
        *
        * @return the next side in clockwise order
        */
Side right(Side side) {
    switch (side) {
    case Side::NORTH:
        return Side::EAST;
    case Side::EAST:
        return Side::SOUTH;
    case Side::SOUTH:
        return Side::WEST;
    case Side::WEST:
        return Side::NORTH;
    default:
        return Side::UNDEFINED;
    }
}

/**
        * Returns the next side in counter-clockwise order.
        *
        * @return the next side in counter-clockwise order
        */
Side left(Side side) {
    switch (side) {
    case Side::NORTH:
        return Side::WEST;
    case Side::EAST:
        return Side::NORTH;
    case Side::SOUTH:
        return Side::EAST;
    case Side::WEST:
        return Side::SOUTH;
    default:
        return Side::UNDEFINED;
    }
}

/**
        * Returns the opposed side.
        *
        * @return the opposed side
        */
Side opposed(Side side) {
    switch (side) {
    case Side::NORTH:
        return Side::SOUTH;
    case Side::EAST:
        return Side::WEST;
    case Side::SOUTH:
        return Side::NORTH;
    case Side::WEST:
        return Side::EAST;
    default:
        return Side::UNDEFINED;
    }
}

/**
        * Get the port side that corresponds to the given direction.
        *
        * @param direction a direction
        * @return the corresponding port side
        */
Side fromDirection(Direction direction) {
    switch (direction) {
    case Direction::UP:
        return Side::NORTH;
    case Direction::RIGHT:
        return Side::EAST;
    case Direction::DOWN:
        return Side::SOUTH;
    case Direction::LEFT:
        return Side::WEST;
    default:
        return Side::UNDEFINED;
    }
}
}
