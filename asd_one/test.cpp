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

	UniformDoubleExtrSearchData uesd(9, 0.0, 5.0, "min", fcnPtr);
	DivideDoubleExtrSearchData desd(0.5, 0.0, 5.0, "min", fcnPtr);

	UnifSearch<double>(uesd);
	std::cout << std::endl;
	DivSearch<double>(desd);

    return 0;
}