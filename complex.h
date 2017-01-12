#ifndef COMPLEX_H
#define COMPLEX_H


class Complex         // класс "Комплексное число"
{
public:
    double Re;
    double Im;
    Complex();
    Complex(double r);
    Complex(double r, double i);
    ~Complex();
    Complex operator + (const Complex &c);//оператор сложения
    Complex operator - (const Complex &c);//оператор вычитания
    Complex operator * (const Complex &c);//оператор умножения
    Complex operator / (const Complex &c); //оператор деления

};
#endif // COMPLEX_H
