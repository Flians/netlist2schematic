#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <regex>
#include <vector>
#include <fstream>

#include "space.h"
#include "shape.h"
#include "include/xml/tinyxml2.h"
#include "include/error/parse_error.h"

namespace ns {

class Port;
class Edge;
class Node;
class Layer;

class Graph
{
protected:
    std::string style;
    Shape shape;
    Space padding;
    // cells included the netlist
    std::set<Node> cells;
    std::vector<Node> unlayered_nodes;
    std::vector<Node> layered_nodes;
    // nodes included the netlist
    std::vector<Node> nodes;
    std::vector<Layer> layers;
    // the input ports included the netlist
    std::vector<Port> input_ports;
    // the output ports included the netlist
    std::vector<Port> output_ports;
    // the defined net included the netlist
    std::vector<Port> netnames;
    std::vector<Edge> edges;


public:
    Graph();
    Graph(const std::string&);
    Graph(const Graph &graph);
    Graph& operator=(const Graph &o);

    ~Graph();
    std::size_t getId();
    void setId(const std::size_t &value);

    Graph &parse_verilog(const std::string &file_name);
    Graph &parse_skin(const std::string &file_name);
    void add_io_node(const std::string &node_name, const std::string &port_name, const std::string &cell_type);
    void add_io_port(const std::string &port_name, const std::string &cell_type);
    void add_cells(const std::string &path, const std::string &cell_type);
private:
    bool verify_file(const std::string&);
    void insert_edge(const std::string&, const std::string&);

};

}

#endif // GRAPH_H
