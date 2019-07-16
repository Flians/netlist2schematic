#include "include/graph/graph.h"
#include "include/graph/port.h"
#include "include/graph/edge.h"
#include "include/graph/node.h"
#include "include/graph/layer.h"
#include "src/util/util_string.cpp"

#include <iostream>

namespace ns {
Graph::Graph()
{
}


Graph::Graph(const std::string& file_name)
{
    parse_verilog(file_name);
}

Graph::Graph(const Graph &graph)
{
    this->style = graph.style;
    this->shape = graph.shape;
    this->padding = graph.padding;
    this->cells = graph.cells;
    this->unlayered_nodes = graph.unlayered_nodes;
    this->layered_nodes = graph.layered_nodes;
    this->nodes = graph.nodes;
    this->layers = graph.layers;
    this->input_ports = graph.input_ports;
    this->output_ports = graph.output_ports;
    this->netnames = graph.netnames;
    this->edges = graph.edges;
}

Graph &Graph::operator=(const Graph &o)
{
    this->style = o.style;
    this->shape = o.shape;
    this->padding = o.padding;
    this->cells = o.cells;
    this->unlayered_nodes = o.unlayered_nodes;
    this->layered_nodes = o.layered_nodes;
    this->nodes = o.nodes;
    this->layers = o.layers;
    this->input_ports = o.input_ports;
    this->output_ports =o.output_ports;
    this->netnames = o.netnames;
    this->edges = o.edges;
    return *this;
}

Graph::~Graph()
{
    this->cells.clear();
    std::set<Node>().swap(this->cells);
    this->nodes.clear();
    std::vector<Node>().swap(this->nodes);
    this->input_ports.clear();
    std::vector<Port>().swap(this->input_ports);
    this->output_ports.clear();
    std::vector<Port>().swap(this->output_ports);
    this->netnames.clear();
    std::vector<Port>().swap(this->netnames);
}

void print_smatch(std::smatch match) {
    for (std::size_t i=0; i < match.size(); i++) {
        std::cout << match[i] << " > ";
    }
    std::cout << std::endl;
}

Graph &Graph::parse_verilog(const std::string& file_name)
{
    if(!verify_file(file_name))
        throw ParseError("The input file not found!");
    std::string line;
    std::ifstream inputFile(file_name.c_str());

    do{
        inputFile >> line;
    } while(line != "module");
    std::getline(inputFile, line);
    line = strip(line);
    this->shape.setName(strip(line.substr(0, line.find_first_of("("))));
    std::vector<std::string> ports_IO = split(line.substr(line.find_first_of("(")+1, line.find_last_of(")")-line.find_first_of("(")-1), ",");

    std::string osp = "[\\t\\n\\r ]*";
    std::string sp = "[\\t\\n\\r ]+";
    std::string delayPart = "((?:#\\(" + osp + "([0-9.]+)" + osp + "," + osp + "([0-9.]+)" + osp + "\\))?)";
    // std::regex wirePattern("(input|output|inout)" + osp + "(\\[\\d+\\:\\d+\\])?" + sp + "((\\w+)" + "([ \\t]*,[ \\t]*(\\w+))*)");
    std::regex wirePattern("(input|output|inout)" + osp + "(\\[\\d+\\:\\d+\\])?" + sp + "([^]+)(?=;)");
    std::regex gatePattern("([A-Za-z0-9]+)" + sp + delayPart + osp + "([_0-9a-zA-z]+)?" + osp + "\\(([^]+)\\)");
    std::regex assignPatern("assign (.+) = 1'b(0|1);");
    std::smatch match;
    while (getline(inputFile, line, '\n')){
        // delete the comment
        line = strip(line);
        std::size_t commentIndex = line.find_first_of("//");
        if (commentIndex != std::string::npos || line.empty()){
            // line.erase(commentIndex);
            continue;
        }

        if (regex_search(line, match, wirePattern)){
            //print_smatch(match);
            std::vector<std::string> port_names = split(strip(match[3].str()));
            for (std::size_t i=0; i < port_names.size(); i++) {
                // parsing the array operator[:]
                std::string arr = strip(match[2].str());
                if (arr.size()){
                    std::vector<std::string> numbers = split(arr,":");
                    if(numbers.size()==2){
                        int firstNumber = atoi(numbers[0].substr(1).c_str());
                        int secondNumber = atoi(numbers[1].substr(0, numbers[1].size()-1).c_str());
                        if (firstNumber < secondNumber) std::swap(firstNumber, secondNumber);
                        for (int j = firstNumber; j >= secondNumber; j--) {
                            this->add_io_port(strip(port_names[i]) + "[" + std::to_string(i) + "]", match[1].str());
                        }
                    } else{
                        throw ParseError("The line '" + line + "' is wrong!");
                    }
                }
                else{
                    this->add_io_port(strip(port_names[i]), match[1].str());
                }

            }
        }
        else if (regex_search(line, match, gatePattern)){
            // print_smatch(match);
            this->add_cells(getDir(file_name), match[1].str());
            Node tnode(this->nodes.size(), match[5].str(), NodeType::NORMAL, match[1].str());
            std::set<Node>::iterator cell = this->cells.find(Node(tnode.getCell_type(), tnode.getCell_type(), NodeType::NODE_CELL));
            if(cell == this->cells.end())
                std::cout << tnode.getCell_type() << " not existed" << std::endl;
            std::vector<std::string> port_names = split(match[6], ",");
            std::size_t i=0;
            try {
                for(; i<cell->getInput_ports().size();i++){
                    Port tport(cell->getInput_ports()[i].getShape().getId(), strip(port_names[i]), PortType::INOUT);
                    tnode.add_port(tport);
                    tport.~Port();
                }
                for (;i<cell->getPortSize();i++) {
                    Port tport(cell->getOutput_ports()[i-cell->getInput_ports().size()].getShape().getId(), strip(port_names[i]), PortType::OUTPUT);
                    tnode.add_port(tport);
                    tport.~Port();
                }
                this->nodes.push_back(tnode);
                tnode.~Node();
            } catch (...) {
                throw ParseError("There is some wrong in '" + line + "' of the file: " + file_name);
            }
        }
        else if (regex_search(line, match, assignPatern)){
            //edges[match[1].str()] = Edge(match[1].str(), this);
            std::string constval = (match[2].str() == "1") ? "CONST_ONE" : "CONST_ZERO";
            //if (!nodeIndex.count(constval))
            //    insertNode(constval);
            //edges[match[1].str()].setSourceNode(nodeIndex[constval]);
        }
    }
    inputFile.close();

    return *this;
}

Graph &Graph::parse_skin(const std::string &file_name)
{
    if(!verify_file(file_name))
        throw ParseError("The input file not found!");

    tinyxml2::XMLDocument skin_doc;
    skin_doc.LoadFile(file_name.c_str());
    tinyxml2::XMLElement* elm_svg = skin_doc.RootElement();
    try {
        for (tinyxml2::XMLElement* it = elm_svg->FirstChildElement(); it; it = it->NextSiblingElement()){
            std::string elm_name = it->Name();
            std::cout << elm_name << "\t";
            //std::cout << it->ToString() << std::endl;
            if (elm_name == "spacing")
            {
                this->padding.setBetween_nodes(it->FirstChildElement("betweenNodes")->DoubleText());
                this->padding.setBetween_layers(it->FirstChildElement("betweenLayers")->DoubleText());
            } else if (elm_name == "style") {
                this->style = it->GetText();
            } else if (elm_name == "g") {
                std::cout << it->Attribute("type") << std::endl;
                Node aim_node(it->Attribute("type"), it->Attribute("type"), NodeType::NODE_CELL);
                std::set<Node>::iterator tnode = this->cells.find(aim_node);
                if (tnode != this->cells.end())
                {
                    aim_node = *tnode;
                    std::string transform = it->Attribute("transform");
                    std::string sp = "[\\t ]*";
                    std::regex transformPattern("(translate)\\((\\d+)" + sp + "," + sp  + "(\\d+)\\)?");
                    std::smatch match;
                    if (regex_search(transform, match, transformPattern)){
                        aim_node.setPosition(match[2], match[3]);
                    }
                    aim_node.setSize(it->DoubleAttribute("width"), it->DoubleAttribute("height"));
                    for (tinyxml2::XMLElement* it_children = it->FirstChildElement(); it_children; it_children = it_children->NextSiblingElement()){
                        std::string ch_name = it_children->Name();
                        std::cout << "\t" << it_children->ToString() << std::endl;
                        if(ch_name == "text")
                            aim_node.add_label(it_children->ToString());
                        if(ch_name == "alias")
                            aim_node.add_label(it_children->ToString());
                        if(ch_name == "path")
                            aim_node.add_path(it_children->ToString());
                        if(ch_name == "g") {
                            std::string portn = it_children->Attribute("pid");
                            aim_node.set_port_position(portn, it_children->DoubleAttribute("x"), it_children->DoubleAttribute("y"));
                        }
                    }
                    this->cells.erase(tnode++);
                } else {
                }
                this->cells.insert(aim_node);
            }
        }
    } catch(...) {
        throw ParseError("Parsing the skin file failed!");
    }

    return *this;
}

void Graph::add_io_node(const std::string &node_name, const std::string &port_name, const std::string &cell_type)
{
    Port tport(this->netnames.size(), port_name, cell_type);

    switch (tport.getType()) {
    case PortType::INPUT:
        this->input_ports.push_back(tport);
        break;
    case PortType::OUTPUT:
        this->output_ports.push_back(tport);
        break;
    case PortType::INOUT:
        this->input_ports.push_back(tport);
        this->output_ports.push_back(tport);
        break;
    default:
        throw ParseError("This Port's PortType is undefined!");
    }

    this->netnames.push_back(tport);

    Node tnode(this->nodes.size(), node_name, NodeType::NODE_IO, cell_type);
    tnode.add_port(tport);
    // put the input/output port into nodes.
    this->nodes.push_back(tnode);
    tnode.setId(this->cells.size());
    // put the input/output port into cells.
    this->cells.insert(tnode);

    tport.~Port();
    tnode.~Node();
}

void Graph::add_io_port(const std::string &port_name, const std::string &cell_type)
{
    Port tport(this->netnames.size(), port_name, cell_type);

    switch (tport.getType()) {
    case PortType::INPUT:
        this->input_ports.push_back(tport);
        break;
    case PortType::OUTPUT:
        this->output_ports.push_back(tport);
        break;
    case PortType::INOUT:
        this->input_ports.push_back(tport);
        this->output_ports.push_back(tport);
        break;
    default:
        throw ParseError("This Port's PortType is undefined!");
    }

    this->netnames.push_back(tport);
    tport.~Port();
}

void Graph::add_cells(const std::string &path, const std::string &cell_type)
{
    // std::cout << path << std::endl;
    Node tnode(this->cells.size(), cell_type, NodeType::NODE_CELL);
    if (this->cells.find(tnode) == this->cells.end()) {
        std::string file_name = path + '/' + cell_type + ".v";
        if(!verify_file(file_name))
            throw ParseError("The file '" + file_name + "' not found!");
        std::string line;
        std::ifstream inputFile(file_name.c_str());
        do{
            inputFile >> line;
        } while(line != "module");
        std::getline(inputFile, line);
        line = strip(line);
        std::smatch match;
        std::regex cellPattern("([_0-9a-zA-z]+)?[\\t\\n\\r ]*\\(([^]+)\\)");
        if (regex_search(line, match, cellPattern)) {
            // print_smatch(match);
            tnode.setCell_type(match[1].str());
            if (tnode.getCell_type() != cell_type)
                throw ParseError("The " + cell_type + " is not matched with " + file_name);

            std::vector<std::string> io_para = split(match[2].str(), ",");
            for (std::size_t i=0; i<io_para.size(); i++) {
                std::vector<std::string> temp = split(strip(io_para[i]), " ");
                Port tport(tnode.getPortSize(), temp[2], temp[0]);
                tnode.add_port(tport);
                tport.~Port();
            }
            this->cells.insert(tnode);
        } else {
            throw ParseError("There is some wrong in 'module " + line + "' of the file: " + file_name);
        }
        inputFile.close();
    }
    tnode.~Node();
}

bool Graph::verify_file(const std::string& file_name)
{
    std::ifstream in(file_name.c_str());
    if (in.fail())
        return false;
    in.close();
    return true;
}

void Graph::insert_edge(const std::string &, const std::string &)
{

}

}

