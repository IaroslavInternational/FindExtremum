#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>

template<typename T>
class _SearchExtr
{
public:
	_SearchExtr(int num_calc, T accur, std::pair<T, T> gap, std::string tag);
public:
	void FindExtr();
private:
	std::pair<int, T> FindMin(std::vector<T>& vecFx);
	std::pair<int, T> FindMax(std::vector<T>& vecFx);
	void UnifSearch();
	void DivSearch();
private:
	/* Данные для методов поиска */
	
	int N;
	T l;
	std::pair<T, T> interval;
	std::string tag;

	/*****************************/
};

typedef _SearchExtr<double> SearchDoubleExtr;
typedef _SearchExtr<float> SearchFloatExtr;
typedef _SearchExtr<int> SearchIntExtr;