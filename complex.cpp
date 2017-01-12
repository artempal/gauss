#include "complex.h"

Complex::Complex()
{

}

Complex::Complex(double r)
{
    Re = r;
    Im = 0;
}
Complex::Complex(double r, double i)
{
    Re = r;
    Im = i;
}
Complex::~Complex()
{

}
Complex Complex::operator + (const Complex &c)
{
    return Complex(Re + c.Re, Im + c.Im);
}
Complex Complex::operator - (const Complex &c)//оператор вычитания
{
    return Complex(Re - c.Re, Im - c.Im);
}
Complex Complex::operator * (const Complex &c)//оператор умножения
{
    return Complex(Re * c.Re - Im * c.Im, Re * c.Im + Im * c.Re);
}
Complex Complex::operator / (const Complex &c) //оператор деления
{
    Complex result;
    result.Re = (Re * c.Re + Im * c.Im) / (c.Re*c.Re + c.Im*c.Im);
    result.Im = (c.Re * Im - c.Im * Re) / (c.Re*c.Re + c.Im*c.Im);
    return result;
}
