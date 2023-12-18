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
	SLocation(float Location_X, float Location_Y, std::string Location_Name = "NULL") :
		_Location_X(Location_X), _Location_Y(Location_Y), _Location_Name(Location_Name) {}
	std::string _Location_Name;
	float _Location_X;
	float _Location_Y;
};

class Location
{
public:
	Location(std::string Location_Name = "") :_Internal_Location(SLocation(0.0f, 0.0f, Location_Name)) {}

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

	Location_Limited(std::string Location_Name) :Location(Location_Name) {}

	unsigned Check_Range()
	{
		unsigned Range_Status{ 0xF };
		if (this->Get_Current_Location()._Location_X > 0)
			if (this->Get_Current_Location()._Location_X > this->Get_Current_Location()._Location_X)
				Range_Status |= SIGNAL_RIGH;
		if (this->Get_Current_Location()._Location_X <= 0)
			if (-this->Get_Current_Location()._Location_X > this->Get_Current_Location()._Location_X)
				Range_Status |= SIGNAL_LEFT;
		if (this->Get_Current_Location()._Location_Y > 0)
			if (this->Get_Current_Location()._Location_Y > this->Get_Current_Location()._Location_Y)
				Range_Status |= SIGNAL_ABOV;
		if (this->Get_Current_Location()._Location_Y <= 0)
			if (-this->Get_Current_Location()._Location_Y > this->Get_Current_Location()._Location_Y)
				Range_Status |= SIGNAL_BELO;
		return Range_Status;
	}

	inline void Set_Range(float Adjust_Height, float Adjust_Width)
	{
		this->Get_Current_Location()._Location_X = Adjust_Width;
		this->Get_Current_Location()._Location_Y = Adjust_Height;
	}
};

static Location Auto_Adjust_Location;

class LocationBase
{
public:
	static LocationBase& GetLocationBase()
	{
		static LocationBase* LocBase{ new LocationBase };
		return *LocBase;
	}

	int New_Location_set(std::string Location_Name, float Init_LocX = 0.0f, float Init_LocY = 0.0f, bool Limited = false)
	{
		if (Limited)
		{
			Location_Limited* Limit = new Location_Limited(Location_Name);
			Limit->Set_Location(Init_LocX, Init_LocY);
			_LocationS.push_back(Limit);
		}
		else
		{
			Location* Loc = new Location(Location_Name);
			Loc->Set_Location(Init_LocX, Init_LocY);
			_LocationS.push_back(Loc);
		}
		return static_cast<int>(_LocationS.size()) - 1;
	}

	float& Get_LocationX(int Pos)
	{
		return this->_LocationS.at(Pos)->Get_Current_Location()._Location_X;
	}

	float& Get_LocationY(int Pos)
	{
		return this->_LocationS.at(Pos)->Get_Current_Location()._Location_Y;
	}

	SLocation& Get_LocationS(int Pos)
	{
		return this->_LocationS.at(Pos)->Get_Current_Location();
	}

	float Adjust_Location(int Pos, ECALCUL_MARKING Marking, float Adjust, bool Is_LocX)
	{
		return this->_LocationS.at(Pos)->Get_Calculated_Location(Marking, Adjust, Is_LocX);
	}

	void Set_Location(int Pos, float LocationX = 0.0f, float LocationY = 0.0f)
	{
		this->_LocationS.at(Pos)->Set_Location(LocationX, LocationY);
	}

private: 
	LocationBase() :_LocationS(0) {}
	~LocationBase() {}
	LocationBase(const LocationBase&) :_LocationS(0) {};
	LocationBase& operator=(const LocationBase&) { return *this; }

	std::vector<Location*> _LocationS;
};

#endif