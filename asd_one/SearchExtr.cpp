#include "SearchExtr.h"
#include <iostream>

template<typename T>
_SearchExtr<T>::_SearchExtr(int num_calc, T accur, std::pair<T, T> gap, std::string tag)
{
	N = num_calc;
	l = accur;
	interval = gap;
	this->tag = tag;
}

template<typename T>
void _SearchExtr<T>::FindExtr()
{
	std::cout << "Вычисление ..." << std::endl;
	UnifSearch();
	system("clear");
}

template<typename T>
std::pair<int, T> _SearchExtr<T>::FindMin(std::vector<T>& vecFx)
{
	T min = vecFx.at(0);
	int index = 0;

	for (int i = 0; i < vecFx.size(); i++)
	{
		if (vecFx.at(i) < min)
		{
			min = vecFx.at(i);
		}
	}

	return std::make_pair<T, T>(index, min);
}

template<typename T>
std::pair<int, T> _SearchExtr<T>::FindMax(std::vector<T>& vecFx)
{
	T max = vecFx.at(0);
	int index = 0;

	for (int i = 0; i < vecFx.size(); i++)
	{
		if (vecFx.at(i) > max)
		{
			max = vecFx.at(i);
		}
	}

	return std::make_pair<T, T>(index, max);
}

std::function<float(float)> fcnPtr
{
	[](float x) {
		return x - 4.0f * sqrt(x + 2.0f) + 5.5f;
	}
};

template<typename T>
void _SearchExtr<T>::UnifSearch()
{
	std::vector<T> x;
	x.reserve(N);

	std::vector<T> fx;
	fx.reserve(N);

	std::pair<int, T> max, min, res_interaval;

	T koef = (interval.second - interval.first) / (N + 1);
	T result;

	for (int i = 1; i < N; i++)
	{
		x.at(i - 1) = interval.first + i * koef;
		fx.at(i - 1) = fcnPtr(x.at(i - 1));
	}

	if (tag == "max")
	{
		max = FindMax(x);
		result = x.at(max.first);
		
		std::cout << "Найденное максимальное значение: " << result << std::endl;
		std::cout << "Кол-во вычислений (N): " << N << std::endl;
		std::cout << "Максимальное значение находится диапазоне: ["
			<< x.at(max.first - 1) << "; " << x.at(max.first + 1) <<
			"]" << std::endl;
	}
	else if (tag == "min")
	{
		min = FindMin(x);
		
		result = x.at(min.first);

		std::cout << "Найденное максимальное значение: " << result << std::endl;
		std::cout << "Кол-во вычислений (N): " << N << std::endl;
		std::cout << "Максимальное значение находится диапазоне: ["
			<< x.at(min.first - 1) << "; " << x.at(min.first + 1) <<
			"]" << std::endl;
	}
}