#pragma once
#include <vector>
#include <functional>

namespace CoreX { namespace Vector
{
    void Apply_Function(std::vector<float>& Vector, const std::function<float(float)>& Function);
    std::vector<float> Apply_Function(const std::vector<float>& Vector, const std::function<float(float)>& Function);

    template<typename T>
    void Fill(std::vector<T>& Vector, T Value, int Length);
    template<typename T>
    std::vector<T> Fill(T Value, int Length);
}}

void CoreX::Vector::Apply_Function(std::vector<float>& parr_Vector, const std::function<float(float)>& pp_Function)
{
    for (auto& E1 : parr_Vector)
        E1 = pp_Function(E1);
}

std::vector<float> CoreX::Vector::Apply_Function(const std::vector<float>& parr_Vector, const std::function<float(float)>& pp_Function) {
    
    std::vector<float> larr_Result;
    larr_Result.reserve(parr_Vector.size());
    for (const auto& E1 : parr_Vector)
        larr_Result.push_back(pp_Function(E1));
    return larr_Result;
}

template<typename T>
void CoreX::Vector::Fill(std::vector<T>& parr_Vector, T pp_Value, int pi_Length)
{
    parr_Vector.reserve(pi_Length);
    for (auto& E1 : parr_Vector)
        E1 = pp_Value;

    for (int C1 = static_cast<int>(parr_Vector.size()); C1 < pi_Length; C1++)
        parr_Vector.push_back(pp_Value);
}
template<typename T>
std::vector<T> CoreX::Vector::Fill(T pp_Value, int pi_Length)
{
    std::vector<T> larr_Data;
    larr_Data.reserve(pi_Length);
    for (int C1 = 0; C1 < pi_Length; C1++)
        larr_Data.push_back(pp_Value);

    return larr_Data;
}