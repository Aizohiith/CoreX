#pragma once
#include <type_traits>
namespace CoreX
{
	template <typename T>
	struct Is_Primitive : std::integral_constant<bool, std::is_arithmetic<T>::value || std::is_enum<T>::value>{};

    template<typename T>
    struct is_vector : std::false_type {};

    template<typename T>
    struct is_vector<std::vector<T>> : std::true_type {};

    template<typename T>
    using vector_value_type = typename std::conditional<is_vector<T>::value, typename T::value_type, T>::type;

    template<typename T>
    struct is_string : std::false_type {};

    template<>
    struct is_string<std::string> : std::true_type {};


}