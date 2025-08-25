//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-16 11:24
// 引擎基础类增加名称参数
// 增加游戏坐标模板类
// 引擎基础类增加名称获取函数
// 移动语言枚举到引擎基础模块中

#pragma once

#ifndef _TANXL_ENGINE_BASE_
#define _TANXL_ENGINE_BASE_

#include <string>

enum ECurren_Language
{
	LANGUAGE_ENGLISH,
	LANGUAGE_CHINESE,
	LANGUAGE_FRENCH,
	LANGUAGE_RUSSIAN,
	LANGUAGE_JAPANESE
};

class Tanxl_ClassBase
{
public:
	Tanxl_ClassBase(std::string Version, std::string Name = "UNDEFINE NAME") :_Version(Version), _Name(Name) {}

	inline std::string Get_Version()
	{
		return this->_Version;
	}

	inline std::string Get_Name()
	{
		return this->_Name;
	}

private:
	const std::string _Version;
	const std::string _Name;
};

#endif