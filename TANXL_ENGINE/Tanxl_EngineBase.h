//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-16 11:24
// 引擎基础类增加名称参数
// 增加游戏坐标模板类

#pragma once

#ifndef _TANXL_ENGINE_BASE_
#define _TANXL_ENGINE_BASE_

#include <string>

template<typename Tanxl_TypeName>
struct Tanxl_Coord
{
	Tanxl_Coord(Tanxl_TypeName Coord_X, Tanxl_TypeName Coord_Y) :
		_Coord_X(Coord_X), _Coord_Y(Coord_Y) {}

	Tanxl_TypeName _Coord_X;
	Tanxl_TypeName _Coord_Y;

	bool operator==(const Tanxl_Coord& Coord)
	{
		if ((this->_Coord_X == Coord._Coord_X) && (this->_Coord_Y == Coord._Coord_Y))
			return true;
		return false;
	}
};

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