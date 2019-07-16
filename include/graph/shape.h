#ifndef SHAPE_H
#define SHAPE_H

#include "nvector.h"

namespace ns {

class Shape
{
public:
    Shape():id(0),name("undefined"){}
    Shape(const std::string &name):id(0),name(name){}
    ~Shape(){}

    Shape &operator=(const Shape &o);

    NVector getPosition() const;
    void setPosition(const NVector &value);
    void setPosition(const double &x, const double &y);

    NVector getSize() const;
    void setSize(const NVector &value);

    std::string getName() const;
    void setName(std::string value);

    std::size_t getId() const;
    void setId(const std::size_t &value);

protected:
    std::size_t id;
    std::string name;
    NVector position;
    NVector size;
};

}

#endif // SHAPE_H
