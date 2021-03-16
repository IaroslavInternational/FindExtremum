#include "Extremum.h"

int main()
{
    setlocale(LC_ALL, "Russian");

	typedef std::function<double(double)> DoubleFunctionF_X;

	DoubleFunctionF_X fcnPtr
	{
		[](double x) {
			return x - 4.0 * sqrt(x + 2.0) + 5.5;
		}
	};

	using namespace Extremum;

	// Поиск экстремума с использованием структур

	UniformDoubleExtrSearchData uesd(9, 0.0, 5.0, "min", fcnPtr);
	DivideDoubleExtrSearchData desd(0.5, 0.0, 5.0, "min", fcnPtr);

	UnifSearch<double>(uesd);
	std::cout << std::endl;
	DivSearch<double>(desd);

	// Поиск экстремума с использованием функций напрямую

	UnifSearch<double>(9, 0.0, 5.0, "min", fcnPtr);
	std::cout << std::endl;
	DivSearch<double>(0.5, 0.0, 5.0, "min", fcnPtr);

    return 0;
}