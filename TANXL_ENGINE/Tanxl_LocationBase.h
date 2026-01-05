//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-20 10:53
// 初始版本
// 将受限移动功能改为独立的类
// 定义全局变量替代绘制模块的自动调整记录成员
// 增加计算并返回坐标的功能
// 增加单例模式的坐标基类
// 基础坐标结构体增加名称成员
// 修正限制坐标类的错误成员设置
// 坐标基类增加添加坐标记录的功能
// 增加简化版本的坐标数据获取功能
// 坐标基类增加调整指定坐标的功能
// 坐标基类增加设置指定坐标的功能
// 整理进入核心层
// 增加版本信息功能
// 修复边缘检测功能错误的问题
// 增加删除已记录的坐标功能
// 修复设置坐标功能错误的问题
// 改为继承自引擎基础类
// 坐标模板结构替换原有坐标结构
// 坐标模板类增加加法重载
// 坐标模板类增加与单数字的比较重载
// 析构函数增加动态添加的数据的处理

#pragma once

#ifndef _TANXL_LOCATIONBASE_
#define _TANXL_LOCATIONBASE_

#include<string>
#include<vector>

#include "Tanxl_EngineBase.h"

enum ELIMIT_RANGE_SIGNAL
{
	SIGNAL_NOTH = 0,
	SIGNAL_LEFT = 1,
	SIGNAL_RIGH = 2,
	SIGNAL_ABOV = 4,
	SIGNAL_BELO = 8
};

enum ECALCUL_MARKING
{
	MARKING_ADD,
	MARKING_SUB,
	MARKING_MUL,
	MARKING_DIV
};

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

	bool operator==(const Tanxl_TypeName& Compare)
	{
		if ((this->_Coord_X == Compare) && (this->_Coord_Y == Compare))
			return true;
		return false;
	}
	
	Tanxl_Coord operator+(Tanxl_Coord& Coord)
	{
		this->_Coord_X += Coord._Coord_X;
		this->_Coord_Y += Coord._Coord_Y;
		return *this;
	}

	Tanxl_Coord operator+=(Tanxl_Coord& Coord)
	{
		this->_Coord_X += Coord._Coord_X;
		this->_Coord_Y += Coord._Coord_Y;
		return *this;
	}

	Tanxl_Coord operator-(Tanxl_Coord& Coord)
	{
		this->_Coord_X -= Coord._Coord_X;
		this->_Coord_Y -= Coord._Coord_Y;
		return *this;
	}

	Tanxl_Coord operator-=(Tanxl_Coord& Coord)
	{
		this->_Coord_X -= Coord._Coord_X;
		this->_Coord_Y -= Coord._Coord_Y;
		return *this;
	}

	Tanxl_Coord operator*(double& Mult)
	{
		this->_Coord_X *= Mult;
		this->_Coord_Y *= Mult;
		return *this;
	}

	Tanxl_Coord operator*=(double& Mult)
	{
		this->_Coord_X *= Mult;
		this->_Coord_Y *= Mult;
		return *this;
	}

	Tanxl_Coord operator/(double& Div)
	{
		this->_Coord_X /= Div;
		this->_Coord_Y /= Div;
		return *this;
	}

	Tanxl_Coord operator/=(double& Div)
	{
		this->_Coord_X /= Div;
		this->_Coord_Y /= Div;
		return *this;
	}
};

class Location
{
public:
	Location(std::string Location_Name = "");
	// 获取坐标结构体
	inline Tanxl_Coord<float>& Get_Current_Location();
	// 调整坐标的两个参数
	inline void Adjust_Location(float Adjust_Height, float Adjust_Width);
	// 设置坐标的两个参数
	inline void Set_Location(float Set_Height, float Set_Width);

	inline float Get_Calculated_Location(ECALCUL_MARKING Marking, float Value, bool begin) const;

private:

	Tanxl_Coord<float> _Internal_Location;
};

class Location_Limited : public Location
{
public:

	Location_Limited(std::string Location_Name);

	unsigned Check_Range();

	inline void Set_Range(float Adjust_Height, float Adjust_Width);
};

class LocationBase : public Tanxl_ClassBase
{
public:
	static LocationBase& GetLocationBase();

	int New_Location_set(std::string Location_Name, float Init_LocX = 0.0f, float Init_LocY = 0.0f, bool Limited = false);

	float& Get_LocationX(int Pos);

	float& Get_LocationY(int Pos);

	Tanxl_Coord<float>& Get_LocationS(int Pos);

	float Adjust_Location(int Pos, ECALCUL_MARKING Marking, float Adjust, bool Is_LocX);

	void Set_Location(int Pos, float LocationX = 0.0f, float LocationY = 0.0f);

	void Remove_LocationS(int Location_Id);// 警告: 在非重置基类的情况下不推荐使用

	const std::string Get_Version();

private: 
	LocationBase();
	~LocationBase();
	LocationBase(const LocationBase&);
	LocationBase& operator=(const LocationBase&);

	std::vector<Location*> _LocationS;
};

#endif