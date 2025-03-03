//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-16 11:24

#pragma once

#ifndef _TANXL_ENGINE_BASE_
#define _TANXL_ENGINE_BASE_

#include <string>

class Tanxl_ClassBase
{
public:
	Tanxl_ClassBase(std::string Version) :_Version(Version) {};

	std::string Get_Version()
	{
		return this->_Version;
	}

private:
	const std::string _Version;
};

#endif