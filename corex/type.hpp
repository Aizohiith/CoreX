

namespace CoreX {
	namespace Type
	{
		template <typename T>
		struct Is_Primitive : std::integral_constant<bool, std::is_arithmetic<T>::value || std::is_enum<T>::value> {};

	}
}