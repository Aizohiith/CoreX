#pragma once
#include <iostream>
#include "types.hpp"

namespace CoreX 
{ 
    namespace Serialize
    {
        // Serialize a generic type to text
        template<typename T>
        std::string Serialize_Text(const T& Data);

        // Specialization for std::string
        template<>
        std::string Serialize_Text(const std::string& Data);

        // Serialize a vector of generic type to text
        template<typename T>
        std::string Serialize_Text(const std::vector<T>& Data);

        // Deserialize a non-vector, non-string type from text
        template<typename T>
        typename std::enable_if<!CoreX::Types::Is_Vector<T>::value && !CoreX::Types::Is_String<T>::value, T>::type
        Deserialize_Text(std::string& Data);

        // Deserialize a vector type from text
        template<typename T>
        typename std::enable_if<CoreX::Types::Is_Vector<T>::value, T>::type
        Deserialize_Text(std::string& Data);

        // Deserialize a string type from text
        template<typename T>
        typename std::enable_if<CoreX::Types::Is_String<T>::value, T>::type
        Deserialize_Text(std::string& Data);

        // Serialize a generic type to binary
        template<typename T>
        std::string Serialize_Binary(const T& Data);

        // Specialization for std::string
        template<>
        std::string Serialize_Binary(const std::string& Data);

        // Serialize a vector to binary
        template<typename T>
        std::string Serialize_Binary(const std::vector<T>& Data);

        // Deserialize a non-vector, non-string type from binary
        template<typename T>
        typename std::enable_if<!CoreX::Types::Is_Vector<T>::value && !CoreX::Types::Is_String<T>::value, T>::type
        Deserialize_Binary(std::string& Data);
        
        // Deserialize a vector type from binary
        template<typename T>
        typename std::enable_if<CoreX::Types::Is_Vector<T>::value, T>::type
        Deserialize_Binary(std::string& Data);

        // Deserialize a string type from binary
        template<typename T>
        typename std::enable_if<CoreX::Types::Is_String<T>::value, T>::type
        Deserialize_Binary(std::string& Data);
    }
}

template<>
std::string CoreX::Serialize::Serialize_Text(const std::string& ps_Data)
{
    std::ostringstream ll_Stream;
    ll_Stream << ps_Data.length() << " ";
    ll_Stream << ps_Data;
    return ll_Stream.str();
}

template<typename T>
std::string CoreX::Serialize::Serialize_Text(const std::vector<T>& parr_Data)
{
    std::ostringstream ll_Stream;
    ll_Stream << parr_Data.size() << " ";

    for (const auto& E1 : parr_Data)
            ll_Stream << E1 << ' ';

    return ll_Stream.str();
}

template<typename T>
typename std::enable_if<CoreX::Types::Is_Vector<T>::value, T>::type
CoreX::Serialize::Deserialize_Text(std::string& ps_Data)
{
    using Element_Type = CoreX::Types::Vector_Value_Type<T>;
    std::istringstream ll_Stream(ps_Data);
    std::vector<Element_Type> larr_Data;
    size_t li_Size = 0;
    ll_Stream >> li_Size;

    for (size_t C1 = 0; C1 < li_Size; C1++)
    {
        Element_Type ll_Element{};
        ll_Stream >> ll_Element;
        larr_Data.push_back(ll_Element);
    }

    size_t li_BytesRead = ll_Stream.tellg();
    if (li_BytesRead != std::string::npos)
        ps_Data.erase(0, li_BytesRead);
       
    return larr_Data;
}

template<typename T>
std::string CoreX::Serialize::Serialize_Text(const T& pp_Data)
{
    std::ostringstream ll_Stream;
    ll_Stream << pp_Data;
    return ll_Stream.str();
}

template<typename T>
typename std::enable_if<!CoreX::Types::Is_Vector<T>::value && !CoreX::Types::Is_String<T>::value, T>::type
CoreX::Serialize::Deserialize_Text(std::string& ps_Data)
{
    std::istringstream ll_Stream(ps_Data);
    T ll_Data{};
    ll_Stream >> ll_Data;

    size_t li_BytesRead = ll_Stream.tellg();
    if (li_BytesRead != std::string::npos)
        ps_Data.erase(0, li_BytesRead);

    return ll_Data;
}

template<typename T>
typename std::enable_if<CoreX::Types::Is_String<T>::value, T>::type
CoreX::Serialize::Deserialize_Text(std::string& ps_Data)
{
    
    std::istringstream ll_Stream(ps_Data);
    size_t li_Length = 0;
    ll_Stream >> li_Length;
    ll_Stream.get();
    std::string ls_Result(li_Length, '\0');
    ll_Stream.read(&ls_Result[0], li_Length);
    size_t li_BytesRead = ll_Stream.tellg();
    if (li_BytesRead != std::string::npos)
        ps_Data.erase(0, li_BytesRead);

    return ls_Result;
}

template<typename T>
std::string CoreX::Serialize::Serialize_Binary(const T& pp_Data)
{
    std::ostringstream  ll_Stream(std::ios::binary);
    ll_Stream.write(reinterpret_cast<const char*>(&pp_Data), sizeof(pp_Data));
    return ll_Stream.str();
}

template<>
std::string CoreX::Serialize::Serialize_Binary(const std::string& ps_Data)
{
    std::ostringstream ll_Stream(std::ios::binary);
    size_t li_Length = ps_Data.length();
    ll_Stream.write(reinterpret_cast<const char*>(&li_Length), sizeof(li_Length));
    ll_Stream.write(ps_Data.data(), li_Length);

    return ll_Stream.str();

}

template<typename T>
std::string CoreX::Serialize::Serialize_Binary(const std::vector<T>& parr_Data)
{
    std::ostringstream ll_Stream(std::ios::binary);
    size_t li_Length = parr_Data.size();
    ll_Stream.write(reinterpret_cast<const char*>(&li_Length), sizeof(li_Length));
    ll_Stream.write(reinterpret_cast<const char*>(parr_Data.data()), li_Length * sizeof(T));

    return ll_Stream.str();

}

template<typename T>
typename std::enable_if<!CoreX::Types::Is_Vector<T>::value && !CoreX::Types::Is_String<T>::value, T>::type
CoreX::Serialize::Deserialize_Binary(std::string& ps_Data)
{
    T ll_Data{};
    std::istringstream ll_Stream(ps_Data, std::ios::binary);
    ll_Stream.read(reinterpret_cast<char*>(&ll_Data), sizeof(ll_Data));
    ps_Data = ps_Data.substr(sizeof(ll_Data));
    return ll_Data;
}

template<typename T>
typename std::enable_if<CoreX::Types::Is_String<T>::value, T>::type
CoreX::Serialize::Deserialize_Binary(std::string& ps_Data)
{
    std::istringstream ll_Stream(ps_Data, std::ios::binary);
    size_t li_Length = 0;
    ll_Stream.read(reinterpret_cast<char*>(&li_Length), sizeof(li_Length));

    std::string ls_Result(li_Length, '\0');
    ll_Stream.read(&ls_Result[0], li_Length);
    ps_Data = ps_Data.substr(sizeof(li_Length) + li_Length);
    
    return ls_Result;
}

template<typename T>
typename std::enable_if<CoreX::Types::Is_Vector<T>::value, T>::type
CoreX::Serialize::Deserialize_Binary(std::string& ps_Data)
{
    using Element_Type = CoreX::Types::Vector_Value_Type<T>;
    std::istringstream ll_Stream(ps_Data, std::ios::binary);
    size_t li_Length = 0;
    ll_Stream.read(reinterpret_cast<char*>(&li_Length), sizeof(li_Length));
    std::vector<Element_Type> larr_Result;
    larr_Result.resize(li_Length);
    
    ll_Stream.read(reinterpret_cast<char*>(larr_Result.data()), li_Length * sizeof(Element_Type));
    ps_Data = ps_Data.substr(li_Length * sizeof(Element_Type) + sizeof(li_Length));

    return larr_Result;
}