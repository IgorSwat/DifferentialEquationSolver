#include "gaussianquadrature.h"
#include <cmath>
using std::vector;

GaussianQuadrature::GaussianQuadrature(int n)
{
    switch (n)
    {
    case 1:
        this->precision = 1;
        this->points.push_back(0.0);
        this->wages.push_back(2.0);
        break;
    case 2:
        this->precision = 2;
        this->points.push_back(-(1.0 / sqrt(3)));
        this->points.push_back(1.0 / sqrt(3));
        this->wages.push_back(1.0);
        this->wages.push_back(1.0);
        break;
    case 3:
        this->precision = 3;
        this->points.push_back(0.0);
        this->points.push_back(-sqrt(3.0 / 5.0));
        this->points.push_back(sqrt(3.0 / 5.0));
        this->wages.push_back(8.0 / 9.0);
        this->wages.push_back(5.0 / 9.0);
        this->wages.push_back(5.0 / 9.0);
        break;
    case 4:
        this->precision = 4;
        this->points.push_back(-sqrt(3.0 / 7.0 + 2.0 * sqrt(6.0 / 5.0) / 7.0));
        this->points.push_back(-sqrt(3.0 / 7.0 - 2.0 * sqrt(6.0 / 5.0) / 7.0));
        this->points.push_back(sqrt(3.0 / 7.0 - 2.0 * sqrt(6.0 / 5.0) / 7.0));
        this->points.push_back(sqrt(3.0 / 7.0 + 2.0 * sqrt(6.0 / 5.0) / 7.0));
        this->wages.push_back((18.0 - sqrt(30.0)) / 36.0);
        this->wages.push_back((18.0 + sqrt(30.0)) / 36.0);
        this->wages.push_back((18.0 + sqrt(30.0)) / 36.0);
        this->wages.push_back((18.0 - sqrt(30.0)) / 36.0);
        break;
    case 5:
    default:
        this->precision = 5;
        this->points.push_back(-(1.0 / 3.0) * sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0)));
        this->points.push_back(-(1.0 / 3.0) * sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0)));
        this->points.push_back(0.0);
        this->points.push_back((1.0 / 3.0) * sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0)));
        this->points.push_back((1.0 / 3.0) * sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0)));
        this->wages.push_back((322.0 - 13.0 * sqrt(70.0)) / 900.0);
        this->wages.push_back((322.0 + 13.0 * sqrt(70.0)) / 900.0);
        this->wages.push_back(128.0 / 225.0);
        this->wages.push_back((322.0 + 13.0 * sqrt(70.0)) / 900.0);
        this->wages.push_back((322.0 - 13.0 * sqrt(70.0)) / 900.0);
        break;
    }
}

double GaussianQuadrature::estimateIntegral(double a, double b, oneDimFunction func)
{
    if (a == b)
        return 0.0;
    double factor1 = (b - a) / 2.0;
    double factor2 = (b + a) / 2.0;
    double integralSum = 0.0;
    for (int i = 0; i < precision; i++)
    {
        double functionValue = func(factor1 * points[i] + factor2);
        integralSum += wages[i] * functionValue;
    }
    integralSum *= factor1;
    return integralSum;
}

double GaussianQuadrature::estimateIntegral(double a, double b, IFunction* func)
{
    if (a == b)
        return 0.0;
    double factor1 = (b - a) / 2.0;
    double factor2 = (b + a) / 2.0;
    double integralSum = 0.0;
    for (int i = 0; i < precision; i++)
    {
        double functionValue = (*func)(factor1 * points[i] + factor2);
        integralSum += wages[i] * functionValue;
    }
    integralSum *= factor1;
    return integralSum;
}
