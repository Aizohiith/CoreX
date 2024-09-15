#pragma once
#include <vector>
#include <functional>

namespace CoreX { namespace Vector
{
    void Apply_Function(std::vector<float>& Vector, const std::function<float(float)>& Function);
    std::vector<float> Apply_Function(const std::vector<float>& Vector, const std::function<float(float)>& Function);

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