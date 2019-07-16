#ifndef LAYER_H
#define LAYER_H

#include <vector>

#include "shape.h"
#include "graph.h"

namespace ns {

class Port;
class Node;

class Layer
{
public:
    Layer();
    Layer& operator=(const Layer &o);

    ~Layer();

protected:
    Shape shape;
    Graph owner;
    std::vector<Node> nodes;
};

}

#endif // LAYER_H
