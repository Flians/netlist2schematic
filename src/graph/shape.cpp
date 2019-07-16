#include "include/graph/shape.h"

namespace ns {

Shape &Shape::operator=(const Shape &o)
{
    this->id = o.id;
    this->name = o.name;
    this->position = o.position;
    this->size = o.size;
    return *this;
}

NVector Shape::getPosition() const
{
    return position;
}

void Shape::setPosition(const NVector &value)
{
    this->position = value;
}

void Shape::setPosition(const double &x, const double &y)
{
    this->position.setX(x);
    this->position.set(y);
}

NVector Shape::getSize() const
{
    return size;
}

void Shape::setSize(const NVector &value)
{
    size = value;
}

std::string Shape::getName() const
{
    return name;
}

void Shape::setName(std::string value)
{
    name = value;
}

std::size_t Shape::getId() const
{
    return id;
}

void Shape::setId(const std::size_t &value)
{
    id = value;
}

}
