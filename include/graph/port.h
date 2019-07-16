#ifndef PORT_H
#define PORT_H

#include <string>
#include <vector>
#include <algorithm>

#include "shape.h"
#include "side.h"
#include "node.h"

namespace ns {

class Edge;

class Port
{
public:
    Port();
    Port(const std::string &name);
    Port(const std::string &name, const PortType &type);
    Port(const size_t id ,const std::string &name, const PortType &type);
    Port(const size_t id ,const std::string &name, const std::string &type);
    Port &operator=(const Port&);

    ~Port();

    PortType getType() const;
    void setType(const PortType &value);

    Shape getShape() const;
    void setShape(const Shape &value);

    Shape setPosition(const double &x, const double &y);

protected:
    Shape shape;
    Node owner;
    PortType type = PortType::UNDEFINED;
    Side side = Side::UNDEFINED;
    std::vector<Edge> input_edges;
    std::vector<Edge> output_edges;
    std::vector<Edge> edges;

private:
    PortType toPortType(const std::string &type);
};
}


#endif // PORT_H
