//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-20 10:53
// 初始版本
// 将受限移动功能改为独立的类
// 定义全局变量替代绘制模块的自动调整记录成员
// 增加计算并返回坐标的功能
// 增加单例模式的坐标基类

#pragma once

#ifndef _TANXL_LOCATIONBASE_
#define _TANXL_LOCATIONBASE_

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

struct SLocation
{
	SLocation(float Location_X, float Location_Y) :
		_Location_X(Location_X), _Location_Y(Location_Y) {}
	float _Location_X;
	float _Location_Y;
};

class Location
{
public:
	Location() :_Internal_Location(SLocation(0.0f, 0.0f)) {}

	inline SLocation& Get_Current_Location()
	{
		return this->_Internal_Location;
	}

	inline void Adjust_Location(float Adjust_Height, float Adjust_Width)
	{
		this->_Internal_Location._Location_X += Adjust_Width;
		this->_Internal_Location._Location_Y += Adjust_Height;
	}

	inline void Set_Location(float Set_Height, float Set_Width)
	{
		this->_Internal_Location._Location_X += Set_Width;
		this->_Internal_Location._Location_Y += Set_Height;
	}

	inline float Get_Calculated_Location(ECALCUL_MARKING Marking, float Value, bool begin)
	{
		float Return_Value{ this->_Internal_Location._Location_Y };
		if (begin)
			Return_Value = this->_Internal_Location._Location_X;
		switch (Marking)
		{
		case MARKING_ADD:
			return (Return_Value + Value);
		case MARKING_SUB:
			return (Return_Value - Value);
		case MARKING_MUL:
			return (Return_Value * Value);
		case MARKING_DIV:
			if (Value == 0)
				return 0;
			return (Return_Value / Value);
		}
		return 0;
	}

private:

	SLocation _Internal_Location;
};

class Location_Limited :public Location
{
public:

	Location_Limited() :Location(), _Limited_Range(SLocation(0.0f, 0.0f)) {}

	unsigned Check_Range()
	{
		unsigned Range_Status{ 0xF };
		if (this->Get_Current_Location()._Location_X > 0)
			if (this->Get_Current_Location()._Location_X > this->_Limited_Range._Location_X)
				Range_Status |= SIGNAL_RIGH;
		if (this->Get_Current_Location()._Location_X <= 0)
			if (-this->Get_Current_Location()._Location_X > this->_Limited_Range._Location_X)
				Range_Status |= SIGNAL_LEFT;
		if (this->Get_Current_Location()._Location_Y > 0)
			if (this->Get_Current_Location()._Location_Y > this->_Limited_Range._Location_Y)
				Range_Status |= SIGNAL_ABOV;
		if (this->Get_Current_Location()._Location_Y <= 0)
			if (-this->Get_Current_Location()._Location_Y > this->_Limited_Range._Location_Y)
				Range_Status |= SIGNAL_BELO;
		return Range_Status;
	}

	inline void Set_Range(float Adjust_Height, float Adjust_Width)
	{
		this->_Limited_Range._Location_X = Adjust_Width;
		this->_Limited_Range._Location_Y = Adjust_Height;
	}

private:
	SLocation _Limited_Range;
};

static Location Auto_Adjust_Location;

class LocationBase
{
public:
	LocationBase& GetLocationBase()
	{
		static LocationBase* LocBase{ new LocationBase };
		return *LocBase;
	}


	Location Auto_Adjust()
	{
		return this->_Auto_Adjust_Location;
	}

private:
	LocationBase() :_Auto_Adjust_Location(Location()) {}
	~LocationBase() {}
	LocationBase(const LocationBase&) :_Auto_Adjust_Location(Location()) {};
	LocationBase& operator=(const LocationBase&) { return *this; }

	Location _Auto_Adjust_Location;
};

#define _Auto_Adjust_Location_X (Auto_Adjust_Location.Get_Current_Location()._Location_X)
#define _Auto_Adjust_Location_Y (Auto_Adjust_Location.Get_Current_Location()._Location_X)

#endif