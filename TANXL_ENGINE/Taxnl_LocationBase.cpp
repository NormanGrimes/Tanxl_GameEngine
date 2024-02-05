#pragma once

#include "Tanxl_LocationBase.h"

SLocation::SLocation(float Location_X, float Location_Y, std::string Location_Name) :
	_Location_X(Location_X), _Location_Y(Location_Y), _Location_Name(Location_Name) {}

Location::Location(std::string Location_Name) :_Internal_Location(SLocation(0.0f, 0.0f, Location_Name)) {}

inline SLocation& Location::Get_Current_Location()
{
	return this->_Internal_Location;
}

inline void Location::Adjust_Location(float Adjust_Height, float Adjust_Width)
{
	this->_Internal_Location._Location_X += Adjust_Width;
	this->_Internal_Location._Location_Y += Adjust_Height;
}

inline void Location::Set_Location(float Set_Height, float Set_Width)
{
	this->_Internal_Location._Location_X += Set_Width;
	this->_Internal_Location._Location_Y += Set_Height;
}

inline float Location::Get_Calculated_Location(ECALCUL_MARKING Marking, float Value, bool begin)
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

Location_Limited::Location_Limited(std::string Location_Name) :Location(Location_Name) {}

unsigned Location_Limited::Check_Range()
{
	unsigned Range_Status{ 0x0 };
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

inline void Location_Limited::Set_Range(float Adjust_Height, float Adjust_Width)
{
	this->Get_Current_Location()._Location_X = Adjust_Width;
	this->Get_Current_Location()._Location_Y = Adjust_Height;
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

float& LocationBase::Get_LocationX(int Pos)
{
	return this->_LocationS.at(Pos)->Get_Current_Location()._Location_X;
}

float& LocationBase::Get_LocationY(int Pos)
{
	return this->_LocationS.at(Pos)->Get_Current_Location()._Location_Y;
}

SLocation& LocationBase::Get_LocationS(int Pos)
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

const std::string LocationBase::Get_Version()
{
	return this->_Version;
}

LocationBase::LocationBase() :_LocationS(0) {}

LocationBase::~LocationBase() {}

LocationBase::LocationBase(const LocationBase&) :_LocationS(0) {};

LocationBase& LocationBase::operator=(const LocationBase&) { return *this; }