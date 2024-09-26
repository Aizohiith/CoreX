#pragma once
#include <cstdlib> 

namespace CoreX { namespace Function
{
	float Relu(const float& Value);
	float Relu_Derivative(const float& Value);

	float Leaky_Relu(const float& Value, const float& Alpha = 0.01f);
	float Leaky_Relu_Derivative(const float& Value, const float& Alpha = 0.01f);

	float Random(const float& Value);
}}

float CoreX::Function::Relu(const float& pf_Value)
{
	return pf_Value < 0.0f ? 0.0f : pf_Value;
}

float CoreX::Function::Relu_Derivative(const float& pf_Value)
{
	return pf_Value > 0.0f ? 1.0f : 0.0f;
}

float CoreX::Function::Leaky_Relu(const float& pf_Value, const float& pf_Alpha)
{
	return pf_Value < 0.0f ? pf_Alpha * pf_Value : pf_Value;
}

float CoreX::Function::Leaky_Relu_Derivative(const float& pf_Value, const float& pf_Alpha)
{
	return pf_Value > 0.0f ? 1.0f : pf_Alpha;
}

float CoreX::Function::Random(const float& input) 
{
	return rand();
}

