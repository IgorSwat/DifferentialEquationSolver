#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <cmath>
#include <vector>
#include <iostream>
using std::vector;
using std::cout;

class IFunction
{
public:
    virtual ~IFunction() {}
    virtual double operator()(double x) const = 0;
    virtual IFunction* df() const = 0;
    virtual void show() const = 0;
};

class LinearFunction : public IFunction
{
private:
    const double a;
    const double b;
public:
    LinearFunction(double aParam = 0.0, double bParam = 0.0) : a(aParam), b(bParam) {}
    virtual double operator()(double x) const {return x*a + b;}
    virtual IFunction* df() const
    {
        return new LinearFunction(0.0, a);
    }
    virtual IFunction* operator*(IFunction* other) const
    {
        return nullptr;
    }
    virtual void show() const
    {
        cout<<a<<"x + "<<b;
    }
    LinearFunction operator+(const LinearFunction& other)
    {
        return LinearFunction(a + other.getAFactor(), b + other.getBFactor());
    }
    double getAFactor() const {return a;}
    double getBFactor() const {return b;}
};

class DoubleFunction : public IFunction
{
private:
    IFunction* first;
    IFunction* second;
    const double leftPoint;
    const double centralPoint;
    const double rightPoint;
public:
    DoubleFunction(IFunction* f1, IFunction* f2, double lPoint, double cPoint, double rPoint)
        : leftPoint(lPoint), centralPoint(cPoint), rightPoint(rPoint)
    {
        this->first = f1;
        this->second = f2;
    }
    virtual double operator()(double x) const
    {
        if (x >= leftPoint && x < centralPoint)
            return (*first)(x);
        if (x >= centralPoint && x <= rightPoint)
            return (*second)(x);
        return 0.0;
    }
    virtual IFunction* df() const
    {
        return new DoubleFunction(first->df(), second->df(), leftPoint, centralPoint, rightPoint);
    }
    virtual void  show() const
    {
        cout<<"{";
        first->show();
        cout<<" dla ("<<leftPoint<<","<<centralPoint<<"); ";
        second->show();
        cout<<" dla ("<<centralPoint<<","<<rightPoint<<")}";
    }
    IFunction* getPartialFunction(double x) const
    {
        if (x >= leftPoint && x < centralPoint)
            return first;
        if (x >= centralPoint && x < rightPoint)
            return second;
        return new LinearFunction();
    }
    double getLeftMargin() {return leftPoint;}
    double getRightMargin() {return rightPoint;}
};

class SumFunction : public IFunction
{
private:
    IFunction* first;
    IFunction* second;
public:
    SumFunction(IFunction* f1, IFunction* f2) {this->first = f1; this->second = f2;}
    virtual double operator()(double x) const {return (*first)(x) + (*second)(x);}
    virtual IFunction* df() const {return new SumFunction(first->df(), second->df());}
    virtual void show() const
    {
        first->show();
        cout<<" + ";
        second->show();
    }
};

class ProductFunction : public IFunction
{
private:
    IFunction* first;
    IFunction* second;
public:
    ProductFunction(IFunction* f1, IFunction* f2) {this->first = f1; this->second = f2;}
    virtual double operator()(double x) const {return (*first)(x) * (*second)(x);}
    virtual IFunction* df() const {return new SumFunction(new ProductFunction(first, second->df()), new ProductFunction(first->df(), second));}
    virtual void show() const
    {
        cout<<"(";
        first->show();
        cout<<") * (";
        second->show();
        cout<<")";
    }
};

class DivideFunction : public IFunction
{
private:
    IFunction* first;
    IFunction* second;
public:
    DivideFunction(IFunction* f1, IFunction* f2) {this->first = f1; this->second = f2;}
    virtual double operator()(double x) const {return (*first)(x) / (*second)(x);}
    virtual IFunction* df() const {return new SumFunction(new ProductFunction(first, second->df()), new ProductFunction(first->df(), second));}
    virtual void show() const
    {
        cout<<"(";
        first->show();
        cout<<") * (";
        second->show();
        cout<<")";
    }
};

class TestingFunctionsGenerator
{
private:
    const double leftPoint;
    const double rightPoint;
    const double diff;
    const int numOfElements;
public:
    TestingFunctionsGenerator(double lPoint, double rPoint, int N) : leftPoint(lPoint),
        rightPoint(rPoint), diff((rPoint - lPoint) / N), numOfElements(N) {}
    vector<DoubleFunction> generateFunctions()
    {
        vector<DoubleFunction> functions = vector<DoubleFunction>();
        functions.push_back(DoubleFunction(new LinearFunction(), new LinearFunction(-1.0 / diff, 1.0 + leftPoint / diff),
                            leftPoint - diff, leftPoint, leftPoint + diff));
        for (int i = 1; i < numOfElements; i++)
        {
            double centralPoint = leftPoint + diff*i;
            double lPoint = leftPoint + (i - 1)*diff;
            double rPoint = leftPoint + (i + 1)*diff;
            LinearFunction* f1 = new LinearFunction(1.0 / diff, -lPoint / diff);
            LinearFunction* f2 = new LinearFunction(-1.0 / diff, rPoint / diff);
            functions.push_back(DoubleFunction(f1, f2, lPoint, centralPoint, rPoint));
        }
        functions.push_back(DoubleFunction(new LinearFunction(1.0 / diff, 1.0 - rightPoint / diff), new LinearFunction(),
                            rightPoint - diff, rightPoint, rightPoint + diff));
        return functions;
    }
};

#endif // FUNCTIONS_H_INCLUDED
