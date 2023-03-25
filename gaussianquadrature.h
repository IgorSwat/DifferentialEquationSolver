#ifndef GAUSSIANQUADRATURE_H
#define GAUSSIANQUADRATURE_H

#include <vector>
#include "functions.h"
typedef double (*oneDimFunction)(double);

class GaussianQuadrature
{
private:
    int precision;
    std::vector<double> points;
    std::vector<double> wages;

public:
    GaussianQuadrature(int n); // Jezeli n wykracza poza zbior {1, 2, 3, 4, 5}, to domyslnie ustawione zostaje n = 5
    double estimateIntegral(double a, double b, oneDimFunction func);
    double estimateIntegral(double a, double b, IFunction* func);
};

#endif // GAUSSIANQUADRATURE_H
