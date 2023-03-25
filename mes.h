#ifndef MES_H
#define MES_H

#include <cmath>
#include <vector>
#include "functions.h"
#include "linearequationssolver.h"
#include "gaussianquadrature.h"
#include "sections.h"
using namespace std;

class MES
{
private:
    int numOfElements;
    const double leftPoint = 0.0;
    const double rightPoint = 3.0;
    const double diff;
    double G;
    LinearFunction* shift;
    vector<DoubleFunction> testingFunctions;
    vector<double> factors;
    GaussianQuadrature* calculusEstimator;
    double B(IFunction* w, IFunction* v, const Section& range) const;
    double L(IFunction* v, const Section& range) const;
    void loadParameters(LinearEquationsSolver& solver);
public:
    MES(int n = 3, bool useG = true);
    ~MES() {delete shift; delete calculusEstimator;}
    vector<double> solve();
    double getValueInPoint(double x) const;
    double getLeftMargin() const {return leftPoint;}
    double getRightMargin() const {return rightPoint;}
};

#endif // MES_H
