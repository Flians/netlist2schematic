#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <algorithm>

#include "port_type.h"
#include "shape.h"
#include "layer.h"
#include "graph.h"

namespace ns {

enum NodeType {
    NORMAL, // a normal node is created from a node of the original graph.
    NODE_IO, // a input/output node.
    NODE_BIG, // a dummy node originating from a node spanning multiple layers.
    NODE_CELL, // a cell node.
    DUMMY_EDGE, // a dummy node created to split a long edge.
    DUMMY_PORT_EXTERNAL, // a node representing an external port.
    DUMMY_PORT_NS, // a dummy node created to cope with ports at the northern or southern side.
    DUMMY_LABEL // a dummy node to represent a mid-label on an edge.
};

class Space;
class Port;

class Node
{
public:
    Node();
    Node(const std::string &cell_type, const NodeType &type);
    Node(const std::string &name, const std::string &cell_type, const NodeType &type);
    Node(const size_t id, const std::string &name, const NodeType &type);
    Node(const size_t id, const std::string &name, const NodeType &type, const std::string &cell_type);
    Node(const Node &node);
    Node &operator=(const Node &o);
    bool operator<(const Node &o) const;

    ~Node();

    void add_port(const Port &p);
    void add_label(const std::string &label);
    void add_path(const std::string &path);
    std::size_t getPortSize() const;
    bool set_port_position(const std::string &port_name, const double &x, const double &y);

    void setPosition(const double &x, const double &y);
    void setPosition(const std::string &x, const std::string &y);

    void setSize(const double &x, const double &y);
    void setSize(const std::string &x, const std::string &y);

    Shape getShape() const;
    void setShape(const Shape &value);

    std::size_t getId();
    void setId(const std::size_t &value);

    std::string getCell_type() const;
    void setCell_type(const std::string &value);

    std::vector<Port> getInput_ports() const;
    void setInput_ports(const std::vector<Port> &value);

    std::vector<Port> getOutput_ports() const;
    void setOutput_ports(const std::vector<Port> &value);

private:
    NodeType toNodeType(const std::string &type);

protected:
    Shape shape;
    std::string cell_type;
    Graph graph;
    Layer layer;
    NodeType type = NodeType::NORMAL;
    std::vector<Port> input_ports;
    std::vector<Port> output_ports;
    std::vector<std::string> labels;
    std::vector<Space> margin;
    std::vector<std::string> paths;
};

}
#endif // NODE_H
