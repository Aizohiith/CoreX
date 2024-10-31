#pragma once
#include <vector>
#include <functional>
#include <algorithm>

namespace CoreX { namespace Vector
{
    inline void Apply_Function(std::vector<float>& Vector, const std::function<float(float)>& Function);
    inline std::vector<float> Apply_Function(const std::vector<float>& Vector, const std::function<float(float)>& Function);

    template<typename T>
    void Fill(std::vector<T>& Data, T Value, int Length);
    template<typename T>
    std::vector<T> Fill(T Value, int Length);


    namespace Sort
    {
        enum Types
        {
            QUICK,
            BUBBLE
        };
        //Sort Vector inplace
        template<typename T>
        void Sort(std::vector<T>& Data, bool Acending = true, Types Type = Types::QUICK);
        //Sort and Return Vector
        template <typename T>
        std::vector<T> Sort(const std::vector<T>& Data, bool Acending = true, Types Type = Types::QUICK);
    }


}}

template <typename T>
void CoreX::Vector::Sort::Sort(std::vector<T>& parr_Data, bool pb_Acending, Types pp_Type)
{

    switch (pp_Type)
    {
        case Sort::Types::QUICK:
        {
            if (pb_Acending)
                std::sort(parr_Data.begin(), parr_Data.end());
            else
                std::sort(parr_Data.begin(), parr_Data.end(), [](const T& A,const T& B) { return A > B; });
        }break;
        case Sort::Types::BUBBLE:
        {
            std::cout << "Herte" << std::endl;
            for (size_t C1 = 0; C1 < parr_Data.size() - 1; C1++)
            {
                for (size_t C2 = C1 + 1; C2 < parr_Data.size(); C2++)
                {
                    if ((parr_Data[C1] > parr_Data[C2]) and (pb_Acending))
                    {
                        T ll_Temp;

                        ll_Temp = parr_Data[C1];
                        parr_Data[C1] = parr_Data[C2];
                        parr_Data[C2] = ll_Temp;
                    }
                    else
                    if ((parr_Data[C1] < parr_Data[C2]) and (!pb_Acending))
                    {
                        T ll_Temp;

                        ll_Temp = parr_Data[C1];
                        parr_Data[C1] = parr_Data[C2];
                        parr_Data[C2] = ll_Temp;
                    }
                }
            }

        }break;
        default: break;
    }
}

template <typename T>
std::vector<T> CoreX::Vector::Sort::Sort(const std::vector<T>& parr_Data, bool pb_Acending, Types pp_Type)
{
    std::vector<T> larr_Result(parr_Data);
    CoreX::Vector::Sort::Sort(larr_Result, pb_Acending, pp_Type);

    return larr_Result;
}

void CoreX::Vector::Apply_Function(std::vector<float>& parr_Vector, const std::function<float(float)>& pp_Function)
{
    for (auto& E1 : parr_Vector)
        E1 = pp_Function(E1);
}

std::vector<float> CoreX::Vector::Apply_Function(const std::vector<float>& parr_Vector, const std::function<float(float)>& pp_Function) {
    
    std::vector<float> larr_Result(parr_Vector);
    Apply_Function(larr_Result, pp_Function);
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