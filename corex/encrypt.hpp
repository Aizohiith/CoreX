#pragma once
#include <iostream>

namespace CoreX { namespace Encrypt
{
	std::string Encrypt_Basic(const std::string& Data, char Key);
	std::string Decrypt_Basic(const std::string& Data, char Key);
}}

std::string CoreX::Encrypt::Encrypt_Basic(const std::string& ps_Data, char pc_Key)
{
	std::string ls_Result;
	ls_Result.reserve(ps_Data.size());

	for (auto& E1 : ps_Data)
	{
		ls_Result +=  (E1 ^ pc_Key);
	}

	return ls_Result;
}

std::string CoreX::Encrypt::Decrypt_Basic(const std::string& ps_Data, char pc_Key)
{
	return Encrypt_Basic(ps_Data, pc_Key);
}