#pragma once
#include <iostream>
#include "corex.hpp"

namespace CoreX { namespace Serialize
{
        template<typename T>
        typename std::enable_if<Is_Primitive<T>::value, std::string>::type
        Serialize_Binary(const T&);

        template<typename T>
        typename std::enable_if<!Is_Primitive<T>::value, std::string>::type
        Serialize_Binary(const T&);

        template<typename T>
        typename std::enable_if<Is_Primitive<T>::value, T>::type
        Deserialize_Binary(const std::string& Data);

        template<typename T>
        typename std::enable_if<!Is_Primitive<T>::value, T>::type
        Deserialize_Binary(const std::string& Data);

        template<typename T>
        typename std::enable_if<Is_Primitive<T>::value, std::string>::type
        Serialize_Text(const T&);

        template<typename T>
        typename std::enable_if<!Is_Primitive<T>::value, std::string>::type
        Serialize_Text(const T&);

        template<typename T>
        typename std::enable_if<Is_Primitive<T>::value, T>::type
        Deserialize_Text(const std::string& Data);

        template<typename T>
        typename std::enable_if<!Is_Primitive<T>::value, T>::type
        Deserialize_Text(const std::string& Data);
}}

template<typename T>
typename std::enable_if<CoreX::Is_Primitive<T>::value, std::string>::type
CoreX::Serialize::Serialize_Binary(const T& pp_Data)
{
    std::ostringstream  ll_Stream(std::ios::binary);

    ll_Stream.write(reinterpret_cast<const char*>(&pp_Data), sizeof(pp_Data));

    return ll_Stream.str();
}

template<typename T>
typename std::enable_if<!CoreX::Is_Primitive<T>::value, std::string>::type
CoreX::Serialize::Serialize_Binary(const T& pp_Data)
{
    static_assert(std::is_member_function_pointer<decltype(&T::Serialize_Binary)>::value, "Input must have a Serialize_Binary method.");
    return pp_Data.Serialize_Binary(pp_Data);
}

template<typename T>
typename std::enable_if<CoreX::Is_Primitive<T>::value, T>::type
CoreX::Serialize::Deserialize_Binary(const std::string& ps_Data)
{
    T ll_Data{};
    std::istringstream ll_Stream(ps_Data, std::ios::binary);
    ll_Stream.read(reinterpret_cast<char*>(&ll_Data), sizeof(ll_Data));
    return ll_Data;
}

template<typename T>
typename std::enable_if<!CoreX::Is_Primitive<T>::value, T>::type
CoreX::Serialize::Deserialize_Binary(const std::string& ps_Data)
{
    static_assert(std::is_member_function_pointer<decltype(&T::Deserialize_Binary)>::value, "Input must have a Deserialize_Binary method.");
    T ll_Data{};
    ll_Data = ll_Data.Deserialize_Binary(ps_Data);
    return ll_Data;
}

template<typename T>
typename std::enable_if<CoreX::Is_Primitive<T>::value, std::string>::type
CoreX::Serialize::Serialize_Text(const T& pp_Data)
{
    std::ostringstream  ll_Stream;
    ll_Stream << pp_Data;
    return ll_Stream.str();
}

template<typename T>
typename std::enable_if<!CoreX::Is_Primitive<T>::value, std::string>::type
CoreX::Serialize::Serialize_Text(const T& pp_Data)
{
    static_assert(std::is_member_function_pointer<decltype(&T::Serialize_Text)>::value, "Input must have a Serialize_Text method.");
    return pp_Data.Serialize_Text(pp_Data);
}

template<typename T>
typename std::enable_if<CoreX::Is_Primitive<T>::value, T>::type
CoreX::Serialize::Deserialize_Text(const std::string& ps_Data)
{
    T ll_Data{};

    std::istringstream ll_Stream(ps_Data);
    ll_Stream >> ll_Data;
    return ll_Data;
}

template<typename T>
typename std::enable_if<!CoreX::Is_Primitive<T>::value, T>::type
CoreX::Serialize::Deserialize_Text(const std::string& ps_Data)
{
    static_assert(std::is_member_function_pointer<decltype(&T::Deserialize_Text)>::value, "Input must have a Deserialize_Text method.");
    T ll_Data{};
    ll_Data = ll_Data.Deserialize_Text(ps_Data);
    return ll_Data;
}
