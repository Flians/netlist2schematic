#ifndef EDGE_H
#define EDGE_H

#include "port.h"

namespace ns {

class Shape;

class Edge
{
public:
    Edge();
    Edge(const std::string &name);
    Edge(const std::string &name, const std::string &type);
    Edge &operator=(const Edge&);

    ~Edge();

    Port getSource() const;
    void setSource(const Port &value);

    Port getTarget() const;
    void setTarget(const Port &value);

    std::vector<std::string> getLabels() const;
    void setLabels(const std::vector<std::string> &value);

    std::vector<Shape> getBendPoints() const;
    void setBendPoints(const std::vector<Shape> &value);

protected:
    std::size_t id;
    std::string name;
    std::string type;
    Port source;
    Port target;
    std::vector<std::string> labels;
    std::vector<Shape> bendPoints;
};

}

#endif // EDGE_H
