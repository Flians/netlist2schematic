#include "include/graph/nvector.h"

namespace ns {
double NVector::getY() const
{
    return y;
}

void NVector::setY(double value)
{
    y = value;
}

NVector &NVector::operator=(const NVector &o)
{
    this->x = o.x;
    this->y = o.y;
    return *this;
}

NVector::~NVector()
{

}

double NVector::getX() const
{
    return x;
}

void NVector::setX(double value)
{
    x = value;
}

void NVector::set(const NVector& o)
{
    this->x = o.x;
    this->y = o.y;
}

std::string NVector::toString()
{
    std::stringstream ss;
    ss << "(" << this->x << "," << this->y << ")";
    return ss.str();
}

bool NVector::equal(const NVector& o)
{
    return fabs(this->x - o.x) == 0 && fabs(this->y - o.y) == 0;
}

bool NVector::equalsFuzzily(const NVector& o, double fuzzyness) {
    return fabs(this->x - o.x) <= fuzzyness
            && fabs(this->y - o.y) <= fuzzyness;
}

double NVector::length()
{
    return sqrt(x * x + y * y);
}

double NVector::squareLength() {
    return x * x + y * y;
}

void NVector::normalize()
{
    double len = this->length();
    if(len > 0)
    {
        this->x /= len;
        this->y /= len;
    }
}

void NVector::add(const NVector &o)
{
    this->x += o.x;
    this->y += o.y;
}

void NVector::add(double dx, double dy)
{
    this->x += dx;
    this->y += dy;
}

void NVector::sub(const NVector &o)
{
    this->x -= o.x;
    this->y -= o.y;
}

void NVector::sub(double dx, double dy)
{
    this->x -= dx;
    this->y -= dy;
}

void NVector::scale(double scale)
{
    this->x *= scale;
    this->y *= scale;
}

double NVector::distance(const NVector& o)
{
    double dx = this->x - o.x;
    double dy = this->y - o.y;
    return sqrt((dx * dx) + (dy * dy));
}

double NVector::dot_product(const NVector &o)
{
    return (this->x * o.x) + (this->y * o.y);
}

bool NVector::isNaN()
{
    return isnan(this->x) || isnan(this->y);
}
}
