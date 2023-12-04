//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-20 10:53
// ³õÊ¼°æ±¾

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

struct SLocation
{
	SLocation(float Location_X, float Location_Y) :
		_Location_X(Location_X), _Location_Y(Location_Y) {}
	float _Location_X;
	float _Location_Y;
};

class LocationBase
{
public:
	LocationBase() :_Internal_Location(SLocation(0.0f, 0.0f)), _Limited_Range(SLocation(0.0f, 0.0f)) {}

	SLocation Get_Current_Location()
	{
		return this->_Internal_Location;
	}

	void Adjust_Location(float Adjust_Height, float Adjust_Width)
	{
		this->_Internal_Location._Location_X += Adjust_Width;
		this->_Internal_Location._Location_Y += Adjust_Height;
	}

	void Set_Location(float Set_Height, float Set_Width)
	{
		this->_Internal_Location._Location_X += Set_Width;
		this->_Internal_Location._Location_Y += Set_Height;
	}

	void Set_Range(float Adjust_Height, float Adjust_Width)
	{
		this->_Limited_Range._Location_X = Adjust_Width;
		this->_Limited_Range._Location_Y = Adjust_Height;
	}

	unsigned Check_Range()
	{
		unsigned Range_Status{ 0xF };
		if (this->_Internal_Location._Location_X > 0)
			if (this->_Internal_Location._Location_X > this->_Limited_Range._Location_X)
				Range_Status |= SIGNAL_RIGH;
		if (this->_Internal_Location._Location_X <= 0)
			if (-this->_Internal_Location._Location_X > this->_Limited_Range._Location_X)
				Range_Status |= SIGNAL_LEFT;
		if (this->_Internal_Location._Location_Y > 0)
			if (this->_Internal_Location._Location_Y > this->_Limited_Range._Location_Y)
				Range_Status |= SIGNAL_ABOV;
		if (this->_Internal_Location._Location_Y <= 0)
			if (-this->_Internal_Location._Location_Y > this->_Limited_Range._Location_Y)
				Range_Status |= SIGNAL_BELO;
		return Range_Status;
	}

private:

	SLocation _Internal_Location;

	SLocation _Limited_Range;
};

#endif