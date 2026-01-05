#pragma once

#include "Tanxl_LocationBase.h"

Location::Location(std::string Location_Name) :_Internal_Location(Tanxl_Coord<float>(0.0f, 0.0f)) {}

inline Tanxl_Coord<float>& Location::Get_Current_Location()
{
	return this->_Internal_Location;
}

inline void Location::Adjust_Location(float Adjust_Height, float Adjust_Width)
{
	this->_Internal_Location._Coord_X += Adjust_Width;
	this->_Internal_Location._Coord_Y += Adjust_Height;
}

inline void Location::Set_Location(float Set_Height, float Set_Width)
{
	this->_Internal_Location._Coord_X = Set_Width;
	this->_Internal_Location._Coord_Y = Set_Height;
}

inline float Location::Get_Calculated_Location(ECALCUL_MARKING Marking, float Value, bool begin) const
{
	float Return_Value{ this->_Internal_Location._Coord_Y };
	if (begin)
		Return_Value = this->_Internal_Location._Coord_X;
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

Location_Limited::Location_Limited(std::string Location_Name) :Location(Location_Name) {}

unsigned Location_Limited::Check_Range()
{
	unsigned Range_Status{ 0x0 };
	if (this->Get_Current_Location()._Coord_X > 0)
		if (this->Get_Current_Location()._Coord_X > this->Get_Current_Location()._Coord_X)
			Range_Status |= SIGNAL_RIGH;
	if (this->Get_Current_Location()._Coord_X <= 0)
		if (-this->Get_Current_Location()._Coord_X > this->Get_Current_Location()._Coord_X)
			Range_Status |= SIGNAL_LEFT;
	if (this->Get_Current_Location()._Coord_Y > 0)
		if (this->Get_Current_Location()._Coord_Y > this->Get_Current_Location()._Coord_Y)
			Range_Status |= SIGNAL_ABOV;
	if (this->Get_Current_Location()._Coord_Y <= 0)
		if (-this->Get_Current_Location()._Coord_Y > this->Get_Current_Location()._Coord_Y)
			Range_Status |= SIGNAL_BELO;
	return Range_Status;
}

inline void Location_Limited::Set_Range(float Adjust_Height, float Adjust_Width)
{
	this->Get_Current_Location()._Coord_X = Adjust_Width;
	this->Get_Current_Location()._Coord_Y = Adjust_Height;
}

LocationBase& LocationBase::GetLocationBase()
{
	static LocationBase* LocBase{ new LocationBase };
	return *LocBase;
}

int LocationBase::New_Location_set(std::string Location_Name, float Init_LocX, float Init_LocY, bool Limited)
{
	if (Limited)
	{
		Location_Limited* Limit{ new Location_Limited(Location_Name) };
		Limit->Set_Location(Init_LocX, Init_LocY);
		this->_LocationS.push_back(Limit);
	}
	else
	{
		Location* Loc{ new Location(Location_Name) };
		Loc->Set_Location(Init_LocX, Init_LocY);
		this->_LocationS.push_back(Loc);
	}
	return static_cast<int>(_LocationS.size()) - 1;
}

float& LocationBase::Get_LocationX(int Pos)
{
	return this->_LocationS.at(Pos)->Get_Current_Location()._Coord_X;
}

float& LocationBase::Get_LocationY(int Pos)
{
	return this->_LocationS.at(Pos)->Get_Current_Location()._Coord_Y;
}

Tanxl_Coord<float>& LocationBase::Get_LocationS(int Pos)
{
	return this->_LocationS.at(Pos)->Get_Current_Location();
}

float LocationBase::Adjust_Location(int Pos, ECALCUL_MARKING Marking, float Adjust, bool Is_LocX)
{
	return this->_LocationS.at(Pos)->Get_Calculated_Location(Marking, Adjust, Is_LocX);
}

void LocationBase::Set_Location(int Pos, float LocationX, float LocationY)
{
	this->_LocationS.at(Pos)->Set_Location(LocationX, LocationY);
}

void LocationBase::Remove_LocationS(int Location_Id)
{
	if (Location_Id < 0)
		std::vector<Location*>().swap(this->_LocationS);
	else
	{
		if (Location_Id < this->_LocationS.size())
		{
			delete this->_LocationS.at(Location_Id);
			this->_LocationS.erase(this->_LocationS.begin() + Location_Id);
		}
	}
}

const std::string LocationBase::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

LocationBase::LocationBase() :_LocationS(0), Tanxl_ClassBase("0.1") {}

LocationBase::~LocationBase() { std::vector<Location*>().swap(this->_LocationS); }

LocationBase::LocationBase(const LocationBase&) :_LocationS(0), Tanxl_ClassBase("0.1") {};

LocationBase& LocationBase::operator=(const LocationBase&) { return *this; }