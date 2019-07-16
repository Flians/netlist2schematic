#include "include/graph/node.h"
#include "include/graph/space.h"
#include "include/graph/port.h"
#include "include/graph/edge.h"

namespace ns {

Node::Node()
{

}

Node::Node(const std::string &cell_type, const NodeType &type)
{
    this->cell_type = cell_type;
    this->type = type;
}

Node::Node(const std::string &name, const std::string &cell_type, const NodeType &type)
{
    this->shape.setName(name);
    this->type = type;
    this->cell_type = cell_type;
}

Node::Node(const size_t id, const std::string &name, const NodeType &type)
{
    this->shape.setId(id);
    this->shape.setName(name);
    this->type = type;
}

Node::Node(const size_t id, const std::string &name, const NodeType &type, const std::string &cell_type)
{
    this->shape.setId(id);
    this->shape.setName(name);
    this->type = type;
    this->cell_type = cell_type;
}

Node::Node(const Node &node)
{
    this->shape = node.shape;
    this->cell_type = node.cell_type;
    this->graph = node.graph;
    this->layer = node.layer;
    this->type = node.type;
    this->input_ports = node.input_ports;
    this->output_ports = node.output_ports;
    this->labels = node.labels;
    this->margin = node.margin;
    this->paths = node.paths;
}

Node::~Node()
{
    this->input_ports.clear();
    std::vector<Port>().swap(this->input_ports);
    this->output_ports.clear();
    std::vector<Port>().swap(this->output_ports);
    this->labels.clear();
    std::vector<std::string>().swap(this->labels);
    this->margin.clear();
    std::vector<Space>().swap(this->margin);
    this->paths.clear();
    std::vector<std::string>().swap(this->paths);
}

std::size_t Node::getId()
{
    return this->shape.getId();
}

void Node::setId(const std::size_t &value)
{
    this->shape.setId(value);
}

std::string Node::getCell_type() const
{
    return cell_type;
}

void Node::setCell_type(const std::string &value)
{
    cell_type = value;
}

std::size_t Node::getPortSize() const
{
    return this->input_ports.size() + this->output_ports.size();
}

bool Node::set_port_position(const std::string &port_name, const double &x, const double &y)
{
    bool result = false;
    for (std::size_t i=0; i<this->input_ports.size(); i++) {
        if(this->input_ports[i].getShape().getName() == port_name) {
            this->input_ports[i].setPosition(x,y);
            result = true;
        }
    }
    if (!result) {
        for (std::size_t i=0; i<this->output_ports.size(); i++) {
            if(this->output_ports[i].getShape().getName() == port_name) {
                this->output_ports[i].setPosition(x,y);
                result = true;
            }
        }
    }
    return result;
}

void Node::setPosition(const double &x, const double &y)
{
    this->shape.setPosition(NVector(x,y));
}

void Node::setPosition(const std::string &x, const std::string &y)
{
    this->shape.setPosition(NVector(atof(x.c_str()),atof(y.c_str())));
}

void Node::setSize(const double &x, const double &y)
{
    this->shape.setSize(NVector(x,y));
}

void Node::setSize(const std::string &x, const std::string &y)
{
    this->shape.setSize(NVector(atof(x.c_str()),atof(y.c_str())));
}

std::vector<Port> Node::getInput_ports() const
{
    return input_ports;
}

void Node::setInput_ports(const std::vector<Port> &value)
{
    input_ports = value;
}

std::vector<Port> Node::getOutput_ports() const
{
    return output_ports;
}

void Node::setOutput_ports(const std::vector<Port> &value)
{
    output_ports = value;
}

void Node::add_port(const Port &p)
{
    switch (p.getType()) {
    case PortType::INPUT:
        this->input_ports.push_back(p);
        break;
    case PortType::OUTPUT:
        this->output_ports.push_back(p);
        break;
    case PortType::INOUT:
        this->input_ports.push_back(p);
        this->output_ports.push_back(p);
        break;
    default:
        throw ParseError("This Port's PortType is undefined!");
    }
}

void Node::add_label(const std::string &label)
{
    this->labels.push_back(label);
}

void Node::add_path(const std::string &path)
{
    this->paths.push_back(path);
}

Shape Node::getShape() const
{
    return shape;
}

void Node::setShape(const Shape &value)
{
    shape = value;
}

Node &Node::operator=(const Node& node)
{
    if(this == &node)
    {
        return *this;
    }
    this->shape = node.shape;
    this->cell_type = node.cell_type;
    this->graph = node.graph;
    this->layer = node.layer;
    this->type = node.type;
    this->input_ports = node.input_ports;
    this->output_ports = node.output_ports;
    this->labels = node.labels;
    this->margin = node.margin;
    this->paths = node.paths;

    return *this;
}

bool Node::operator<(const Node &o) const
{
    if(this->cell_type < o.cell_type)
        return true;
    else if(this->cell_type == o.cell_type && this->type < o.type)
        return true;
    else if(this->cell_type == o.cell_type && this->type == o.type
            && this->shape.getName() < o.shape.getName())
        return true;
    return false;
}

}
