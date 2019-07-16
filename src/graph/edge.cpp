#include "include/graph/edge.h"
#include "include/graph/shape.h"

namespace ns {

Edge::Edge()
{

}

Edge::Edge(const std::string &name)
{
    this->name = name;
}

Edge::Edge(const std::string &name, const std::string &type)
{
    this->name = name;
    this->type = type;
}

Edge &Edge::operator=(const Edge &o)
{
    this->id = o.id;
    this->name = o.name;
    this->source = o.source;
    this->target = o.target;
    this->labels = o.labels;
    this->bendPoints = o.bendPoints;

    return *this;
}

Edge::~Edge()
{

}

Port Edge::getSource() const
{
    return source;
}

void Edge::setSource(const Port &value)
{
    source = value;
}

Port Edge::getTarget() const
{
    return target;
}

void Edge::setTarget(const Port &value)
{
    target = value;
}

std::vector<std::string> Edge::getLabels() const
{
    return labels;
}

void Edge::setLabels(const std::vector<std::string> &value)
{
    labels = value;
}

std::vector<Shape> Edge::getBendPoints() const
{
    return bendPoints;
}

void Edge::setBendPoints(const std::vector<Shape> &value)
{
    bendPoints = value;
}

}
