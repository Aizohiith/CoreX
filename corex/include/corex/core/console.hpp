#pragma once
#include <iostream>

namespace CoreX 
{ 
    namespace Console
{

        static const char* RED = "\033[31m";
        static const char* RESET = "\033[0m";

        template<typename T>
        void Print(const T& Data);
        template<typename T>
        void Print_Line(const T& Data);

        template<typename T>
        void Print_Error(const T& Data);
        template<typename T>
        void Print_Error_Line(const T& Data);

        void New_Line(int LineCount = 1);

}}
template<typename T>
void CoreX::Console::Print(const T& pp_Data)
{
    std::cout << pp_Data;
}
template<typename T>
void CoreX::Console::Print_Line(const T& pp_Data)
{
    std::cout << pp_Data << std::endl;
}
template<typename T>
void CoreX::Console::Print_Error(const T& pp_Data)
{
    std::cerr << pp_Data;
}
template<typename T>
void CoreX::Console::Print_Error_Line(const T& pp_Data)
{
    std::cerr << RED << pp_Data << RESET << std::endl;
}

void CoreX::Console::New_Line(int pi_Line_Count)
{
    if (pi_Line_Count <= 0)
        return;
    for (int C1 = 0; C1 < pi_Line_Count; C1++)
        std::cout << std::endl;
}
