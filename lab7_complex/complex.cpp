#include "complex.h"

template <typename T>
std::ostream& operator << (std::ostream & out, const Complex<T> &rhs)
{
	out << "Real : " << rhs.real << " Imag : " << rhs.imag << std::endl;
	return out;
}

template <typename T>
Complex<T>& Complex<T>::operator = (const Complex<T> &rhs) 
{
	real = rhs.real;
	imag = rhs.imag;
	return *this;
}

template <typename T>
Complex<T> Complex<T>::Addition(const Complex & a1, const Complex & a2) 
{
	real = a1.real + a2.real;
	imag = a1.imag + a2.imag;
	return *this;
}

template <typename T>
Complex<T> Complex<T>::Subtraction(const Complex<T> & a1, const Complex<T> & a2) 
{
	real = a1.real - a2.real;
	imag = a1.imag - a2.imag;
	return *this;
}
template <typename T>
Complex<T> Complex<T>::Multiplication(const Complex<T> & a1, const Complex<T> & a2) 
{
	real = a1.real * a2.real - a1.imag * a2.imag;
	imag = a1.real * a2.imag + a2.real * a1.imag;
	return *this;
}

template <typename T>
void Complex<T>::ShowComplexNumber() const
{
	std::cout << "Real : " << real << " Imag : " << imag << std::endl;
}

template <typename T>
Complex<T> Complex<T>::operator + (const Complex<T> &rhs) const
{
	return Complex(real + rhs.real, imag + rhs.imag);
}

template <typename T>
Complex<T> Complex<T>::operator - (const Complex<T> &rhs) const
{
	return Complex(real - rhs.real, imag - rhs.imag);
}

template <typename T>
Complex<T> Complex<T>::operator * (const Complex<T> &rhs) const
{
	return Complex(real * rhs.real - imag * rhs.imag, real * rhs.imag + imag * rhs.real);
}

template <typename T>
Complex<T> Complex<T>::operator () (T re, T im) 
{
	real = re;
	imag = im;
	return *this;
}

template <typename T>
Complex<T> Complex<T>::Vectors_Addition(Complex<T> * v1, Complex<T> * v2, const int size) 
{
	for (int i = 0; i < size; i++)
	{
		this[i](v1[i].Real() + v2[i].Real(), v1[i].Imag() + v2[i].Imag());
	}
	return *this;
}

template <typename T>
void Complex<T>::ShowVector(const int size) const
{
	std::cout << "Vector:" << std::endl;
	for (int i = 0; i < size; i++)
		this[i].Complex<int>::ShowComplexNumber();
}
