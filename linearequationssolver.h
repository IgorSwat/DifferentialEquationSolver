#ifndef LINEAREQUATIONSSOLVER_H
#define LINEAREQUATIONSSOLVER_H
#include "matrixrow.h"
using namespace std;

class LinearEquationsSolver
{
private:
    int height;
    int variablesNum;
    vector<MatrixRow*> matrix;
    void swapRows(int id1, int id2);
    void transformRows(int startID);
    bool repairMainRow(int mainRowID);
    vector<double> readValues();
public:
    LinearEquationsSolver(int variables) {this->height = 0; this->variablesNum = variables;}
    bool loadMatrixRow(MatrixRow* row);
    bool deleteMatrixRow(int rowID);
    vector<double> solveEquations();
};

#endif // LINEAREQUATIONSSOLVER_H
