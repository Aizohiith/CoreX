#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace CoreX 
{ 
    namespace FileIO
    {
        // Save data of any type that supports stream insertion (operator<<) to a file.
        template<typename T>
        bool Save(const std::string& Filename, const T& Data);

        // Load data from a file and return it as a string.
        std::string Load(const std::string& Filename);

    }
}

template<typename T>
bool CoreX::FileIO::Save(const std::string& ps_Filename, const T& ps_Data)
{
    try
    {
        std::ofstream ll_Output_File(ps_Filename, std::ios::out | std::ios::binary);
        

        if (!ll_Output_File)
        {
            std::cerr << "\"" << ps_Filename << "\" - Error: Could not open file for writing" << std::endl;
            return false;
        }
        ll_Output_File.exceptions(std::ios::failbit | std::ios::badbit);
        ll_Output_File << ps_Data;
        ll_Output_File.close();
        return true;
    }
    catch (const std::ofstream::failure& pp_Error)
    {
        std::cerr << "\"" << ps_Filename << "\" - Error: during file write-> " << pp_Error.what() << std::endl;
        return false;
    }
        
    
}

std::string CoreX::FileIO::Load(const std::string& ps_Filename)
{
    std::string ls_Result;
    try
    {
        std::ifstream ll_Input_File(ps_Filename, std::ios::in | std::ios::binary);
        
        if (!ll_Input_File)
        {
            std::cerr << "\"" << ps_Filename << "\" - Error: Could not open file for reading" << std::endl;
            return ls_Result;
        }
        ll_Input_File.exceptions(std::ios::failbit | std::ios::badbit);
        std::string ls_Result((std::istreambuf_iterator<char>(ll_Input_File)), std::istreambuf_iterator<char>());
        ll_Input_File.close();

        return ls_Result;
    }
    catch (const std::ifstream::failure& pp_Error)
    {
        std::cerr << "\"" << ps_Filename << "\" - Error: during file read-> " << pp_Error.what() << std::endl;
        return ls_Result;
    }
}