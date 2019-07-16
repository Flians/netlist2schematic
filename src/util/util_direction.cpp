#include "include/graph/direction.h"

namespace ns {
/**
 * Checks if this layout direction is horizontal. (that is, left or right) An undefined layout
 * direction is not horizontal.
 *
 * @return {@code trure} if the layout direction is horizontal.
 */
bool isHorizontal(Direction dir) {
    return dir == Direction::LEFT || dir == Direction::RIGHT;
}

/**
 * Checks if this layout direction is vertical. (that is, up or down) An undefined layout
 * direction is not vertical.
 *
 * @return {@code trure} if the layout direction is vertical.
 */
bool isVertical(Direction dir) {
    return dir == Direction::UP || dir == Direction::DOWN;
}

/**
 * @return the opposite direction of {@code this}. For instance, if this is {@link #LEFT},
 *         return {@link #RIGHT}.
 */
Direction opposite(Direction dir) {
    switch (dir) {
    case Direction::LEFT:
        return Direction::RIGHT;
    case Direction::RIGHT:
        return Direction::LEFT;
    case Direction::UP:
        return Direction::DOWN;
    case Direction::DOWN:
        return Direction::UP;
    default:
        return Direction::UNDEFINED;
    }
}

}
