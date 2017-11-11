#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

template <class T>
class Complex
{
public:
	Complex(void) : real(0), imag(0) {}
	Complex(T re, T im) : real(re), imag(im) {}
	~Complex() {}
	T& Real() { return real; }
	T& Imag() { return imag; }

	Complex<T> Addition(const Complex<T> & a1, const Complex<T> & a2);
	Complex<T> Subtraction(const Complex<T> & a1, const Complex<T> & a2);
	Complex<T> Multiplication(const Complex<T> & a1, const Complex<T> & a2);
	void ShowComplexNumber();

	Complex<T> operator + (const Complex<T> & rhs);
	Complex<T> operator - (const Complex<T> & rhs);
	Complex<T> operator * (const Complex<T> & rhs);
	Complex<T>& operator = (const Complex<T> &rhs);
	Complex<T> operator () (T re, T im);
	friend std::ostream& operator << (std::ostream & out, const Complex<T> & rhs);

	Complex<T> Complex<T>::Vectors_Addition(Complex<T> * v1, Complex<T> * v2, const int size);
	void ShowVector(const int size);
private:
	T real;
	T imag;
};

#endif // COMPLEX_H