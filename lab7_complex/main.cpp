#include "complex.cpp"
const int N = 3;

int main(void)
{
	Complex<int> v1[N];
	Complex<int> v2[N];
	try
	{
		if (sizeof(v1) / sizeof(Complex<int>) != sizeof(v2) / sizeof(Complex<int>))
			throw "Exception: incorrect dimention";

		for (int i = 0; i < N; i++)
		{
			v1[i](i + 1, i + 1);
			v2[i](i, i);  //fill v1 and v2 
		}
	}
	catch (const char* s)
	{
		std::cout << s << std::endl;
		return 0;
	}

	try
	{
		const int size = sizeof(v1) / sizeof(Complex<int>);
		v1->Complex<int>::ShowVector(size);
		v2->Complex<int>::ShowVector(sizeof(v2) / sizeof(Complex<int>));

		if (size != sizeof(v2) / sizeof(Complex<int>))
			throw "Exception: incorrect dimention";

		Complex<int> v_res[size];
		v_res->Complex<int>::Vectors_Addition(v1, v2, size);

		v_res->Complex<int>::ShowVector(size);
	}
	catch (const char* s)
	{
		std::cout << s << std::endl;
		return 0;
	}

	system("pause");
	return 0;
}