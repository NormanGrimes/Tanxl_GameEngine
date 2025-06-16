//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-16 11:24
// ����������������Ʋ���
// ������Ϸ����ģ����

#pragma once

#ifndef _TANXL_ENGINE_BASE_
#define _TANXL_ENGINE_BASE_

#include <string>

class Tanxl_ClassBase
{
public:
	Tanxl_ClassBase(std::string Version, std::string Name = "UNDEFINE NAME") :_Version(Version), _Name(Name) {}

	std::string Get_Version()
	{
		return this->_Version;
	}

private:
	const std::string _Version;
	const std::string _Name;
};

#endif