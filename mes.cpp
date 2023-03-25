#include "mes.h"
#include <iostream>
# define M_PI           3.14159265358979323846

MES::MES(int n, bool useG) : diff((rightPoint - leftPoint) / n)
{
    if (useG)
        this->G = 6.6743015151515 * pow(10, -11);
    else
        this->G = 1.0;
    this->numOfElements = n;
    this->factors = vector<double>();
    this->shift = new LinearFunction(-1.0 / 3, 5.0);
    TestingFunctionsGenerator generator = TestingFunctionsGenerator(leftPoint, rightPoint, numOfElements);
    this->testingFunctions = generator.generateFunctions();
    this->calculusEstimator = new GaussianQuadrature(4);
}

double MES::B(IFunction* w, IFunction* v, const Section& range) const
{
    IFunction* dw = w->df();
    IFunction* dv = v->df();
    ProductFunction* product = new ProductFunction(dw, dv);
    double value = -calculusEstimator->estimateIntegral(range.a, range.b, product);
    delete dw;
    delete dv;
    delete product;
    return value;
}

double MES::L(IFunction* v, const Section& range) const
{
    double left = 1.0;
    double right = 2.0;
    if (range.a > 1 && range.a <= 2)
        left = range.a;
    if (range.b < 2 && range.b >= 1)
        right = range.b;
    return (4.0 * M_PI * G * calculusEstimator->estimateIntegral(left, right, v) - B(shift, v, range));
}

void MES::loadParameters(LinearEquationsSolver& solver)
{
    vector<double> vals;
    for (int i = 1; i < numOfElements; i++)
    {
        Section range2 = Section(testingFunctions[i].getLeftMargin(), testingFunctions[i].getRightMargin());
        for (int j = 1; j < numOfElements; j++)
        {
            Section range1 = Section(testingFunctions[j].getLeftMargin(), testingFunctions[j].getRightMargin());
            vals.push_back(B(&testingFunctions[j], &testingFunctions[i], range1.intersection(range2)));
        }
        solver.loadMatrixRow(new MatrixRow(vals, L(&testingFunctions[i], range2)));
        vals.clear();
    }
}

vector<double> MES::solve()
{
    if (factors.size() == 0)
    {
        LinearEquationsSolver matrixSolver = LinearEquationsSolver(numOfElements - 1);
        loadParameters(matrixSolver);
        vector<double> wParams = matrixSolver.solveEquations();
        wParams.insert(wParams.begin(), 0);
        wParams.push_back(0);
        this->factors = wParams;
        return wParams;
    }
}

double MES::getValueInPoint(double x) const
{
    if (factors.size() == 0 || x < 0 || x > 3)
        return nan("");
    if (x == 0.0 || x == 3.0)
        return (*shift)(x);
    int elementID = int(x / diff);
    double value = 0.0;
    value += factors[elementID] * testingFunctions[elementID](x);
    value += factors[elementID + 1] * testingFunctions[elementID + 1](x);
    value += (*shift)(x);
    return value;
}
