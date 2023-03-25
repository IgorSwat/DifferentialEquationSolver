#include "matrixrow.h"
using std::vector;
using std::initializer_list;

MatrixRow::MatrixRow(int n, double constant)
{
    this->length = n;
    this->values = vector<double>(length);
    this->values.push_back(constant);
}

MatrixRow::MatrixRow(double* vals, int n, double constant)
{
    this->length = n;
    this->values = vector<double>(n);
    for (int i = 0; i < n; i++)
        this->values[i] = vals[i];
    this->values.push_back(constant);
}

MatrixRow::MatrixRow(const vector<double>& vals, double constant)
{
    this->length = vals.size();
    this->values = vector<double>(length);
    for (int i = 0; i < length; i++)
        this->values[i] = vals[i];
    this->values.push_back(constant);
}

MatrixRow::MatrixRow(const initializer_list<double>& vals, double constant)
{
    this->length = vals.size();
    for (auto i = vals.begin(); i != vals.end(); i++)
        this->values.push_back(*i);
    this->values.push_back(constant);
}

MatrixRow MatrixRow::operator*(double r)
{
    MatrixRow transformedRow = MatrixRow(length, getRowConstant() * r);
    for (int i = 0; i < length; i++)
        transformedRow[i] = this->values[i] * r;
    return transformedRow;
}

MatrixRow operator*(double r, MatrixRow& row)
{
    return row*r;
}

MatrixRow MatrixRow::operator*=(double r)
{
    for (int i = 0; i < length + 1; i++)
        this->values[i] *= r;
    return (*this);
}

MatrixRow MatrixRow::operator+(const MatrixRow& other)
{
    MatrixRow transformedRow = MatrixRow(length, getRowConstant() + other.getRowConstant());
    for (int i = 0; i < length; i++)
        transformedRow[i] = this->values[i] + other[i];
    return transformedRow;
}

MatrixRow MatrixRow::operator+=(const MatrixRow& other)
{
    for (int i = 0; i < length + 1; i++)
        this->values[i] += other[i];
    return (*this);
}
