#pragma once

namespace CoreX { namespace Math
{
		//Return maximum between 2 inputs
		template<typename T>
		T Max(const T&, const T&);

		//Return minimum between 2 inputs
		template<typename T>
		T Min(const T&, const T&);
}}

template<typename T>
T CoreX::Math::Max(const T& pp_A, const T& pp_B)
{
	if (pp_A > pp_B)
		return pp_A;
	else
		return pp_B;
}

template<typename T>
T CoreX::Math::Min(const T& pp_A, const T& pp_B)
{
	if (pp_A < pp_B)
		return pp_A;
	else
		return pp_B;
}