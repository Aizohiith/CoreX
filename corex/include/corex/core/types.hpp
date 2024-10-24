#pragma once
#include <type_traits>
#include <vector>
#include <string>

namespace CoreX 
{
	namespace Types
	{
        // Checks if a type is primitive (arithmetic or enum)
        template <typename T>
        struct Is_Primitive : std::integral_constant<bool, std::is_arithmetic<T>::value || std::is_enum<T>::value> {};

        // Checks if a type is a std::vector
        template<typename T>
        struct Is_Vector : std::false_type {};
        template<typename T>
        struct Is_Vector<std::vector<T>> : std::true_type {};

        // Provides the value type of a vector, or the type itself if not a vector
        template<typename T>
        using Vector_Value_Type = typename std::conditional<Is_Vector<T>::value, typename T::value_type, T>::type;

        // Checks if a type is a std::string
        template<typename T>
        struct Is_String : std::false_type {};
        template<>
        struct Is_String<std::string> : std::true_type {};
	}
}