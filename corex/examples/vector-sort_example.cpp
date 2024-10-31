#define EXAMPLE 0
#if EXAMPLE == 1

#include <iostream>
#include "corex/core/vector.hpp"

void Log(const char* Name, const std::vector<int>& Vector)
{
	std::cout << Name << ": ";
	for (auto& E1 : Vector)
		std::cout << E1 << " ";
	std::cout << std::endl;
}

int main()
{
	std::vector<int> Vector = { 1, 9, 2, 8, 3, 7, 4, 6, 5, 5 };
	Log("Original", Vector);

	std::vector<int> Result = CoreX::Vector::Sort::Sort(static_cast<const std::vector<int>>(Vector));
	std::vector<int> Result_Bubble = CoreX::Vector::Sort::Sort(static_cast<const std::vector<int>>(Vector), false, CoreX::Vector::Sort::Types::BUBBLE);

	Log("Result", Result);
	Log("Result Bubble", Result_Bubble);
	Log("Original", Vector);

	CoreX::Vector::Sort::Sort(Vector, false);
	Log("Original Sorted", Vector);
		
	return 0;
}
#endif