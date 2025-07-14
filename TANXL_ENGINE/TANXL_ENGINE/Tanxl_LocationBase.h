//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-03-20 10:53
// ��ʼ�汾
// �������ƶ����ܸ�Ϊ��������
// ����ȫ�ֱ����������ģ����Զ�������¼��Ա
// ���Ӽ��㲢��������Ĺ���
// ���ӵ���ģʽ���������
// ��������ṹ���������Ƴ�Ա
// ��������������Ĵ����Ա����
// �������������������¼�Ĺ���
// ���Ӽ򻯰汾���������ݻ�ȡ����
// ����������ӵ���ָ������Ĺ���
// ���������������ָ������Ĺ���
// ���������Ĳ�
// ���Ӱ汾��Ϣ����
// �޸���Ե��⹦�ܴ��������
// ����ɾ���Ѽ�¼�����깦��
// �޸��������깦�ܴ��������
// ��Ϊ�̳������������
// ����ģ��ṹ�滻ԭ������ṹ

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
};

class Location
{
public:
	Location(std::string Location_Name = "");
	// ��ȡ����ṹ��
	inline Tanxl_Coord<float>& Get_Current_Location();
	// �����������������
	inline void Adjust_Location(float Adjust_Height, float Adjust_Width);
	// �����������������
	inline void Set_Location(float Set_Height, float Set_Width);

	inline float Get_Calculated_Location(ECALCUL_MARKING Marking, float Value, bool begin);

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

	void Remove_LocationS(int Location_Id);// ����: �ڷ����û��������²��Ƽ�ʹ��

	const std::string Get_Version();

private: 
	LocationBase();
	~LocationBase();
	LocationBase(const LocationBase&);
	LocationBase& operator=(const LocationBase&);

	std::vector<Location*> _LocationS;
};

#endif