#ifndef SPACE_H
#define SPACE_H

#include <string>

namespace ns {

class Space {
protected:
    double between_layers = 10.0;
    double between_nodes = 35.0;
    /** The spacing from the top. */
    double top = 0.0;
    /** The spacing from the bottom. */
    double bottom = 0.0;
    /** The spacing from the left. */
    double left = 0.0;
    /** The spacing from the right. */
    double right = 0.0;

public:
    Space();
    Space(double top, double right, double bottom, double left) {
        set(top, right, bottom, left);
    }
    Space(double between_layers, double between_nodes);
    Space &operator=(const Space&);

    ~Space();

    void set(double between_layers, double between_nodes);
    void set(double newTop, double newRight, double newBottom, double newLeft);
    double getTop() const;
    void setTop(double value);
    double getBottom() const;
    void setBottom(double value);
    double getLeft() const;
    void setLeft(double value);
    double getRight() const;
    void setRight(double value);
    double getBetween_layers() const;
    void setBetween_layers(double value);
    double getBetween_nodes() const;
    void setBetween_nodes(double value);
    std::string toString();
};

}
#endif // SPACE_H
