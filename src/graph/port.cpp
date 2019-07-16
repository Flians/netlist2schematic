#include "include/graph/port.h"
#include "include/graph/edge.h"

namespace ns {
Port::Port()
{

}

Port::Port(const std::string &name)
{
    this->shape.setName(name);
}

Port::Port(const size_t id, const std::string &name, const PortType &type)
{
    this->shape.setId(id);
    this->shape.setName(name);
    this->type=type;
}

Port::Port(const size_t id, const std::string &name, const std::string &type)
{
    this->shape.setId(id);
    this->shape.setName(name);
    this->type = this->toPortType(type);
}

Port::Port(const std::string &name, const PortType &type)
{
    this->shape.setName(name);
    this->type=type;
}

Port &Port::operator=(const Port &o)
{
    /*
    this->id = o.id;
    this->name = o.name;
    this->position = o.position;
    this->size = o.size;
    */
    this->shape = o.shape;
    this->owner = o.owner;
    this->type =o.type;

    this->side = o.side;
    this->input_edges = o.input_edges;
    this->output_edges = o.output_edges;
    this->edges = o.edges;
    return *this;
}

Port::~Port()
{
    this->input_edges.clear();
    std::vector<Edge>().swap(this->input_edges);
    this->output_edges.clear();
    std::vector<Edge>().swap(this->output_edges);
    this->edges.clear();
    std::vector<Edge>().swap(this->edges);
}

PortType Port::getType() const
{
    return type;
}

void Port::setType(const PortType &value)
{
    type = value;
}

Shape Port::getShape() const
{
    return shape;
}

void Port::setShape(const Shape &value)
{
    shape = value;
}

Shape Port::setPosition(const double &x, const double &y)
{
    this->shape.setPosition(x,y);
}

PortType Port::toPortType(const std::string &type) {
    std::string low;
    low.resize(type.size());
    transform(type.begin(), type.end(), low.begin(), tolower);
    if(low == "input"){
        return PortType::INPUT;
    } else if (low == "output") {
        return PortType::OUTPUT;
    } else if (low == "inout") {
        return PortType::INOUT;
    } else {
        return PortType::UNDEFINED;
    }
}


}
