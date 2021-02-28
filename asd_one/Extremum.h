#pragma once

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <functional>

namespace Extremum
{
	template<typename T>
	struct UniformExtrSearchData
	{
		template<typename T>
		UniformExtrSearchData(size_t N, T a, T b, std::string tag, std::function<T(T)> fcnPtr)
		{
			this->N = N;
			this->a = a;
			this->b = b;
			this->tag = tag;
			this->fcnPtr = fcnPtr;
		}

		int N;
		T a;
		T b;
		std::string tag;

		std::function<T(T)> fcnPtr;
	};

	template<typename T>
	struct DivideExtrSearchData
	{
		template<typename T>
		DivideExtrSearchData(T l, T a, T b, std::string tag, std::function<T(T)> fcnPtr)
		{
			this->l = l;
			this->a = a;
			this->b = b;
			this->tag = tag;
			this->fcnPtr = fcnPtr;
		}

		T l;
		T a;
		T b;
		std::string tag;

		std::function<T(T)> fcnPtr;
	};

	template<typename T>
	std::pair<int, T> FindMin(std::vector<T>& vecFx)
	{
		T min = vecFx.at(0);
		int index = 0;

		for (int i = 0; i < vecFx.size(); i++)
		{
			if (vecFx.at(i) < min)
			{
				min = vecFx.at(i);
				index = i;
			}
		}

		return std::pair<int, T>(index, min);
	}

	template<typename T>
	std::pair<int, T> FindMax(std::vector<T>& vecFx)
	{
		T max = vecFx.at(0);
		int index = 0;

		for (int i = 0; i < vecFx.size(); i++)
		{
			if (vecFx.at(i) > max)
			{
				max = vecFx.at(i);
				index = i;
			}
		}

		return std::pair<int, T>(index, max);
	}

	template<typename T>
	void UnifSearch(UniformExtrSearchData<T>& uextr)
	{
		std::vector<T> x;
		x.reserve(uextr.N);

		std::vector<T> fx;
		fx.reserve(uextr.N);

		std::pair<int, T> max, min;

		T koef = (uextr.b - uextr.a) / (uextr.N + 1.0);
		T result;

		for (int i = 1; i <= uextr.N; i++)
		{
			x.push_back(uextr.a + i * koef);
			fx.push_back(uextr.fcnPtr(x.at(i - 1)));
		}

		if (uextr.tag == "max")
		{
			max = FindMax(fx);
			result = x.at(max.first);

			T ub, lb;

			if (max.first + 1 >= x.size())
			{
				ub = x.at(max.first) + koef;
			}
			else
			{
				ub = x.at(max.first + 1);
			}

			if (max.first - 1 < 0)
			{
				lb = x.at(max.first) - koef;
			}
			else
			{
				lb = x.at(max.first - 1);
			}

			std::cout << "Найденное максимальное значение: " << max.second << " при x: " << result << std::endl;
			std::cout << "Кол-во вычислений (N): " << uextr.N << std::endl;
			std::cout << "Максимальное значение находится в диапазоне по абсциссе: ["
				<< lb << "; " << ub <<
				"]" << std::endl;
		}
		else if (uextr.tag == "min")
		{
			min = FindMin(fx);
			result = x.at(min.first);

			T ub, lb;

			if (min.first + 1 > x.size())
			{
				ub = x.at(min.first) + koef;
			}
			else
			{
				ub = x.at(min.first + 1);
			}

			if (min.first - 1 < 0)
			{
				lb = x.at(min.first) - koef;
			}
			else
			{
				lb = x.at(min.first - 1);
			}

			std::cout << "Найденное минимальное значение: " << min.second << " при x: " << result << std::endl;
			std::cout << "Кол-во вычислений (N): " << uextr.N << std::endl;
			std::cout << "Минимальное значение находится в диапазоне по абсциссе: ["
				<< lb << "; " << ub <<
				"]" << std::endl;
		}
	}

	template<typename T>
	void DivSearch(DivideExtrSearchData<T>& dextr)
	{
		T x = (T)0.0;
		int N = 1;
		T sigma = (T)(dextr.l / 2) - (T)(dextr.l / 4);

		T a = dextr.a;
		T b = dextr.b;

		do
		{
			x = (a + b) / 2.0;

			T l = x - sigma;
			T r = x + sigma;

			if (dextr.tag == "max")
			{
				if (dextr.fcnPtr(l) >= dextr.fcnPtr(r))
				{
					b = r;
				}
				else if (dextr.fcnPtr(l) < dextr.fcnPtr(r))
				{
					a = l;
				}
			}
			else if (dextr.tag == "min")
			{
				if (dextr.fcnPtr(l) <= dextr.fcnPtr(r))
				{
					b = r;
				}
				else if (dextr.fcnPtr(l) > dextr.fcnPtr(r))
				{
					a = l;
				}
			}

			N++;
		} 
		while (abs(a - b) > dextr.l);

		if (dextr.tag == "max")
		{
			std::cout << "Найденное максимальное значение: " << dextr.fcnPtr(x) << " при x: " << x << std::endl;
			std::cout << "Кол-во вычислений (N): " << N << std::endl;
			std::cout << "Максимальное значение находится в диапазоне по абсициссе: ["
				<< a << "; " << b <<
				"]" << std::endl;
		}
		else if (dextr.tag == "min")
		{
			std::cout << "Найденное минимальное значение: " << dextr.fcnPtr(x) << " при x: " << x << std::endl;
			std::cout << "Кол-во вычислений (N): " << N << std::endl;
			std::cout << "Минимальное значение находится в диапазоне по абсциссе: ["
				<< a << "; " << b <<
				"]" << std::endl;
		}
	}

	typedef UniformExtrSearchData<double> UniformDoubleExtrSearchData;
	typedef UniformExtrSearchData<float> UniformFloatExtrSearchData;
	typedef UniformExtrSearchData<int> UniformIntExtrSearchData;

	typedef DivideExtrSearchData<double> DivideDoubleExtrSearchData;
	typedef DivideExtrSearchData<float> DivideFloatExtrSearchData;
	typedef DivideExtrSearchData<int> DivideIntExtrSearchData;
}