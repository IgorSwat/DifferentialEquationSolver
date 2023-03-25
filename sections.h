#ifndef SECTIONS_H_INCLUDED
#define SECTIONS_H_INCLUDED
#include <cmath>

class Section
{
public:
    double a;
    double b;
    Section(double first, double second)
    {
        this->a = std::min(first, second);
        this->b = std::max(first, second);
    }
    Section intersection(const Section& other)
    {
        double first = std::max(a, other.a);
        double second = std::min(b, other.b);
        if (first > second)
            return Section(0.0, 0.0);
        return Section(first, second);
    }
    bool isInside(double x)
    {
        return a <= x && x <= b;
    }
};

#endif // SECTIONS_H_INCLUDED
