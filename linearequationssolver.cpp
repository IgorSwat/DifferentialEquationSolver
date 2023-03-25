#include "linearequationssolver.h"
using std::vector;

void LinearEquationsSolver::swapRows(int id1, int id2)
{
    MatrixRow* tmp = this->matrix[id1];
    this->matrix[id1] = matrix[id2];
    this->matrix[id2] = tmp;
}

void LinearEquationsSolver::transformRows(int startID)
{
    MatrixRow* transformingRow = matrix[startID];
    for (int i = startID + 1; i < height; i++)
    {
        if ((*matrix[i])[startID] == 0)
            continue;
        double scalar = -(*matrix[i])[startID];
        (*matrix[i]) += (*transformingRow) * scalar;
    }
}

bool LinearEquationsSolver::repairMainRow(int mainRowID)
{
    for (int i = mainRowID + 1; i < height; i++)
    {
        if ((*matrix[i])[mainRowID] != 0)
        {
            swapRows(mainRowID, i);
            return true;
        }
    }
    return false;
}

vector<double> LinearEquationsSolver::readValues()
{
    vector<double> values;
    int rowSize = matrix[0]->getLength();
    for (int i = height - 1; i >= 0; i--)
    {
        double constant = matrix[i]->getRowConstant();
        for (int j = 0; j < values.size(); j++)
            constant -= (*matrix[i])[rowSize - 1 - j] * values[j];
        double factor = (*matrix[i])[rowSize - 1 - values.size()];
        if (factor != 0)
            values.push_back(constant / factor);
    }
    return vector<double>(values.rbegin(), values.rend());
}

bool LinearEquationsSolver::loadMatrixRow(MatrixRow* row)
{
    if (row->getLength() != variablesNum)
        return false;
    this->matrix.push_back(row);
    this->height++;
    return true;
}

bool LinearEquationsSolver::deleteMatrixRow(int rowID)
{
    if (rowID < 0 || rowID >= height)
        return false;
    this->matrix.erase(matrix.begin() + rowID);
    this->height--;
    return true;
}

vector<double> LinearEquationsSolver::solveEquations()
{
    if (variablesNum != height)
        return vector<double>(0);
    for (int i = 0; i < height; i++)
    {
        if ((*matrix[i])[i] == 0)
            repairMainRow(i);
        if ((*matrix[i])[i] != 0)
        {
            double factor = 1.0 / (*matrix[i])[i];
            (*matrix[i]) *= factor;
            transformRows(i);
        }
    }
    vector<double> results = readValues();
    if (results.size() != variablesNum)
        return vector<double>(0);
    return results;
}
