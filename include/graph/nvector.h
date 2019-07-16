#ifndef NVector_H
#define NVector_H

#include <math.h>
#include <string>
#include <sstream>

namespace ns {

class NVector
{
protected:
    double x;
    double y;

public:
    NVector(): x(0.0),y(0.0){}
    NVector(double x, double y): x(x),y(y){}
    NVector(const NVector& v): x(v.x),y(v.y){}
    NVector(const NVector& start, const NVector& end): x(end.x-start.x),y(end.y-start.y){}
    NVector(double angle):x(cos(angle)), y(sin(angle)){}
    NVector &operator=(const NVector &o);

    virtual ~NVector();
    virtual NVector* clone() {return new NVector(*this);}

    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);
        void set(const NVector& o);
    std::string toString();
    bool equal(const NVector& o);
    bool equalsFuzzily(const NVector& o, double fuzzyness);
    double length();
    double squareLength();
    void normalize();

    void add(const NVector& o);
    void add(double dx, double dy);
    void sub(const NVector& o);
    void sub(double dx, double dy);
    void scale(double scale);
    double distance(const NVector& o);
    double dot_product(const NVector& o);
    bool isNaN();
};

}

#endif // NVector_H
