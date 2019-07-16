#include "include/graph/layer.h"
#include "include/graph/port.h"
#include "include/graph/edge.h"
#include "include/graph/node.h"

namespace ns {
Layer::Layer()
{

}

Layer &Layer::operator=(const Layer &o)
{
    /*
    this->id = o.id;
    this->name = o.name;
    this->position = o.position;
    this->size = o.size;
    */
    this->shape = o.shape;
    this->owner = o.owner;
    this->nodes = o.nodes;
    return *this;
}

Layer::~Layer()
{

}

}
