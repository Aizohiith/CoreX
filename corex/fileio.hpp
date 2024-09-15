#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace CoreX { namespace FileIO
{
    template<typename T>
    bool Save(const std::string& Filename, const T& Data);

    std::string Load(const std::string& Filename);

}}

template<typename T>
bool CoreX::FileIO::Save(const std::string& ps_Filename, const T& ps_Data)
{
    try
    {
        std::ofstream ll_Output_File(ps_Filename, std::ios::out | std::ios::binary);
        ll_Output_File.exceptions(std::ios::failbit | std::ios::badbit);

        if (!ll_Output_File)
        {
            std::cerr << "Error: Could not open file for writing: " << ps_Filename << std::endl;
            return false;
        }

        ll_Output_File << ps_Data;
        ll_Output_File.close();
        return true;
    }
    catch (const std::ofstream::failure& pp_Error)
    {
        std::cerr << "Exception during file write: " << pp_Error.what() << std::endl;
        return false;
    }
        
    
}

std::string CoreX::FileIO::Load(const std::string& ps_Filename)
{
    std::string ls_Data;
    try
    {
        std::ifstream ll_Input_File(ps_Filename, std::ios::in | std::ios::binary);
        ll_Input_File.exceptions(std::ios::failbit | std::ios::badbit);

        if (!ll_Input_File)
        {
            std::cerr << "Error: Could not open file for reading: " << ps_Filename << std::endl;
            return ls_Data;
        }

        std::string ls_Data((std::istreambuf_iterator<char>(ll_Input_File)), std::istreambuf_iterator<char>());
        ll_Input_File.close();

        return ls_Data;
    }
    catch (const std::ifstream::failure& pp_Error)
    {
        std::cerr << "Exception during file read: " << pp_Error.what() << std::endl;
        return ls_Data;
    }
}