#include "include/graph/space.h"

namespace ns {

double Space::getBetween_layers() const
{
    return between_layers;
}

void Space::setBetween_layers(double value)
{
    between_layers = value;
}

double Space::getBetween_nodes() const
{
    return between_nodes;
}

void Space::setBetween_nodes(double value)
{
    between_nodes = value;
}

std::string Space::toString()
{
    return "{" + std::to_string(this->between_layers) + "," + std::to_string(this->between_nodes) + "}";
}

Space::Space(){
    this->top = 0.0;
    this->left = 0.0;
    this->right = 0.0;
    this->bottom = 0.0;
    this->between_layers = 10.0;
    this->between_nodes = 35.0;
}

Space::Space(double between_layers, double between_nodes)
{
    this->between_layers = between_layers;
    this->between_nodes = between_nodes;
}

Space &Space::operator=(const Space &s)
{
    this->top = s.top;
    this->left = s.top;
    this->right = s.right;
    this->bottom = s.bottom;
    return *this;
}

Space::~Space()
{

}

void Space::set(double between_layers, double between_nodes)
{
    this->between_layers = between_layers;
    this->between_nodes = between_nodes;
}

void Space::set(double newTop, double newRight, double newBottom, double newLeft) {
    this->top = newTop;
    this->right = newRight;
    this->bottom = newBottom;
    this->left = newLeft;
}

double Space::getBottom() const
{
    return bottom;
}

void Space::setBottom(double value)
{
    bottom = value;
}

double Space::getLeft() const
{
    return left;
}

void Space::setLeft(double value)
{
    left = value;
}

double Space::getRight() const
{
    return right;
}

void Space::setRight(double value)
{
    right = value;
}

double Space::getTop() const
{
    return top;
}

void Space::setTop(double value)
{
    top = value;
}

}
