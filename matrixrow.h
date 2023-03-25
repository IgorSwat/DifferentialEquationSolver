#ifndef MATRIXROW_H
#define MATRIXROW_H

#include <vector>
#include <initializer_list>
using std::vector;
using std::initializer_list;

class MatrixRow
{
private:
    int length;
    vector<double> values;
public:
    MatrixRow() {}
    MatrixRow(int n, double constant = 0.0);
    MatrixRow(double* vals, int n, double constant = 0.0);
    MatrixRow(const vector<double>& vals, double constant = 0.0);
    MatrixRow(const initializer_list<double>& vals, double constant = 0.0);
    MatrixRow operator*(double r);
    friend MatrixRow operator*(double r, const MatrixRow& row);
    MatrixRow operator*=(double r);
    MatrixRow operator+(const MatrixRow& other);
    MatrixRow operator+=(const MatrixRow& other);
    double& operator[](int i) {return this->values[i];}
    const double& operator[](int i) const {return this->values[i];}
    int getLength() const {return this->length;}
    double getRowConstant() const {return values[length];}
};

#endif // MATRIXROW_H
