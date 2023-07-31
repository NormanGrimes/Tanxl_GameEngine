//_VERSION_2_0_ UPDATE LOG
// LAST_UPDATE 2023-01-31 14:15
// 添加物品功能可选在添加后不清理数据
// 修复整理数据函数中未对应修改尾部/OTH的值
// V4_UPDATE 增加第四版私有结构体的设置函数
// V4_UPDATE 增加第四版的序号数据结构
// V4_UPDATE 为数据数据结构增加一种数据添加方式
// V4_UPDATE 数据数据结构增加取代式添加方式
// V4_UPDATE 增加内部私有结构体的数据设置功能与对应枚举
// V4_UPDATE 内部私有结构体增加序号与数据添加与否的标记
// V4_UPDATE 增加第四版的数据添加功能与对应功能枚举
// V4_UPDATE 增加第四版的数据结构清理功能
// V4 UPDATE 增加第四版的序号结构定位功能

#pragma once

#ifndef _TANXL_DATABASE_
#define _TANXL_DATABASE_

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"Tanxl_DataDefine.h"

enum EAppendItem_Mode
{
	APPENDTO_FILE,
	APPENDTO_MEMO,
	APPENDTO_BOTH
};

enum ELinkSet_Mode
{
	SIMPLE_SET,
	APPEND_CUR,
	APPEND_TAK
};

enum ESort_Mode//为SortDataBase函数提供的功能枚举
{
	SORT_LOCALF,
	FILE_UNITED,
	SORT_MEMORY,
	MEMO_UNITED
};

enum EDivid_Mode//为Divid_Char函数提供的功能枚举
{
	GET_STATUS_DAT,
	GET_STORAG_DAT,
	GET_STATUS_TAG,
	GET_STATUS_STR,
	GET_OLDSTY_DAT
};

enum ESet_Specified
{
	SET_TYPE_STATUS,
	SET_EXAC_STATUS,
	SET_OTH1_STATUS,
	SET_OTH2_STATUS,
	SET_OTH3_STATUS
};

struct Data_Unit
{
	Data_Unit(int Id, std::string Data) :_Id(Id), _Data(Data), _Next(nullptr) {};

	int _Id;
	std::string _Data;
	Data_Unit* _Next;
};

struct Data_Link_V4//数据数据结构V4
{
	explicit Data_Link_V4(int Id, std::string Data)
	{
		_Data_Units.push_back(Data_Unit(Id, Data));
	}
	explicit Data_Link_V4(Data_Unit Data)
	{
		_Data_Units.push_back(Data);
	}
	explicit Data_Link_V4(Data_Link_V4* DataLink)
	{
		this->_Data_Units = DataLink->_Data_Units;
	}
	void Append_Data(int Id, std::string Data)
	{
		_Data_Units.push_back(Data_Unit(Id, Data));
	}
	void Append_Data(Data_Unit Data)
	{
		_Data_Units.push_back(Data);
	}
	void Append_Data(Data_Link_V4* Data, bool Replace = false)
	{
		if (Replace)
		{
			this->_Data_Units.erase(Data->_Data_Units.begin(), Data->_Data_Units.end());
			this->_Data_Units.clear();
		}
		for (int i{ 0 }; i < Data->_Data_Units.size(); ++i)
			this->_Data_Units.push_back(Data->_Data_Units.at(i));
		Data->_Data_Units.erase(Data->_Data_Units.begin(), Data->_Data_Units.end());
		Data->_Data_Units.clear();
	}

	std::vector<Data_Unit> _Data_Units;
};

struct Id_Link_V4//序号数据结构V4
{
	explicit Id_Link_V4(int Type, std::string Type_Name, int Exac, std::string Exac_Name, Data_Link_V4* Data = nullptr) :
		_Type(Type), _Type_Name(Type_Name), _Exac(Exac), _Exac_Name(Exac_Name), _Next(Data) {}
	void Append_Data_Link(Data_Link_V4* Data)
	{
		if (_Next == nullptr)
			_Next = Data;
		else
			_Next->Append_Data(Data);
	}
	int _Type, _Exac;
	std::string _Type_Name, _Exac_Name;
	Data_Link_V4* _Next;
};

struct Data_Vector//短数据表(Vector)
{
	explicit Data_Vector(int I_A = 0xFF, std::string D_A = NULL, int I_B = 0xFF, std::string D_B = NULL, int I_C = 0xFF, std::string D_C = NULL) :
		Id_1(I_A), Id_2(I_B), Id_3(I_C), Sd_1(D_A), Sd_2(D_B), Sd_3(D_C) {}
	int Id_1, Id_2, Id_3;
	std::string Sd_1, Sd_2, Sd_3;
};

struct Id_Vector//短类型表(Vector)
{
	explicit Id_Vector(int Type, int Exac, std::string Code = "NULL", std::string Name = "NULL") :
		Type(Type), Exac(Exac), StrA(Code), StrB(Name), exac(new std::vector<Data_Vector*>) {}
	int Type, Exac;
	std::string StrA, StrB;
	std::vector<Data_Vector*>* exac;//用于支持折半查找
};

class TANXL_DataBase
{
private:
	struct
	{
		unsigned long Item_Status{ 0xFFFFFFFF };
		unsigned Status_1{ 0xF }; std::string Code{};
		unsigned Status_2{ 0xF }; std::string Name{};
		unsigned Status_3{ 0xFF }; std::string Oth1{};
		unsigned Status_4{ 0xFF }; std::string Oth2{};
		unsigned Status_5{ 0xFF }; std::string Oth3{};
	}Item_Instance;

	struct
	{
		unsigned int _Item_Status{ 0xFFFF };//Type 8位 Exac 8位
		std::string _Type_Name{ "" };
		std::string _Exac_Name{ "" };
		Data_Link_V4* _Data{ nullptr };

		bool _Type_Set{ false };
		bool _Data_Set{ false };
	}_Internal_Data;

	const std::string _Version{ "2.0" };
	std::vector<Id_Link_V4*>* _Id_Links;
	std::vector<Id_Vector*>* IC_Vector;
	int Current_Location;
	bool Is_Instance_Data;//用来判断Item_Instance中是否有数据
	bool Is_Chain_Empty;//用来判断链表是否为空
	Id_Vector* Id_Chain_Locate(int Type, int Exac);//时间复杂度为logN的Id_Chain快速定位函数 Type Exac 指Id_Chain的同名变量
	Id_Link_V4* Id_Link_Locate(int Type, int Exac);
	Data_Vector* Data_Chain_Locate(int Type, int Exac, int Depth);//借由Id_Chain_Locate函数对不同深度的Data_Chain定位
	void Replace_Chain(int OldType, int OldExac, int OldDepth, int Type, int Exac);//转移Data_Chain到另一个Id_Chain下
	void Append_Chain(Data_Vector& New_Data, Id_Vector& New_Id);//链表添加内容V3 添加到Vector中
	void Get_Item_Status();//获取物品数值 并加载到结构中
	void Clear_Chain();//清理链表
	void ResetInstance();//重置Item结构的内容
	void ResetInstance_V4();//重置Item结构的内容
	inline void OstreamSpace(std::ostream& os, int Before = 0, int After = 0);//根据级别输出空格 Before用于执行前对级别数值进行修改 After用于执行后
	inline void Combine_Status();//组合Status各物品级别并合并到Item_Instance中
public:
	TANXL_DataBase();//构造函数
	bool Get_LocalData(std::string File_Name);//获取本地数据 并新建一个链表 支持打开任意格式的文件(.usd .sd)

	//↓编辑实例 0x12030405 1代表Code位 2代表Name位 03代表Oth1位 依此类推
	//↓在1.7版本中考虑到零合法的操作一致性 最大值已被作为不可选标志即 Code/Name位的F 或Oth位的FF
	void Set_Instance(unsigned Num, std::string Set);
	void Set_Internal_Id_V4(unsigned Status, std::string Type_Name, std::string Exac_Name);
	void Set_Internal_Data_V4(Data_Link_V4* Data, ELinkSet_Mode Set_Mode);

	//↓读取指定Type(A)_Exac(B)级别的物品 并载入到单例结构中 Nums表示该级别下的第几个物品(从0开始)
	void Get_Specified(int Type, int Exac, int Nums);
	//↓修改指定Type(A)_Exac(B)级别的物品 Nums表示链表中的第几个(从0开始) level取值范围为1~5 用于选定Type Exac Oth1 ...
	//↓修改OTH1 OTH2 OTH3的时候直接更改相关内容 修改TYPE-EXAC时 会转移当前Data_Chain到新的符合修改后的TYPE-EXAC的Id_Chain下
	void Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data);
	void Remove_Chain(int Type, int Exac);//删除某一节点与其下所有内容
	//↓输出当前内存中的链表的所有内容 仅支持输出Id_Vector和Data_Vector中的内容 当前内存为空时会抛出错误
	void Print_Data();

	//↓向本地文件中(.usd)添加Item物品 此函数会导致Item单例重置 To_File为true时会向文件输出 否则存储到内存中 File_Name指定文件名称 不需要添加后缀 Keep_Instance可在为true时 完成添加后不清理Instance数据
	void AppendItem(bool To_File = true, std::string File_Name = "Tanxl_DataBase", bool Keep_Instance = false);
	void AppendItem_V4(EAppendItem_Mode Mode, std::string File_Name = "Tanxl_Data");

	//↓使本地(.usd)文件的内容合理化 In_File_Name为输入文件名 Out_File_Name为输出文件名 现在具有保存链表修改功能
	//↓Mode为true时从文件中读取数据 需要提供In/Out_File_Name 执行后清空内存中的链表  Mode为false时直接对当前内存中的链表进行整理 可以使现有链表改为升序 执行后不清空
	//↓Delete_After_Sort为true时 在数据处理完成之后会删除处理前的原文件 为false则不会删除
	void SortDataBase(int Mode = SORT_LOCALF, std::string Out_File_Name = "Tanxl_Data", std::string In_File_Name = "Tanxl_DataBase",bool Delete_After_Sort = false);
	//↓获取当前存储模块的版本信息
	const std::string Get_Version();
	friend std::ostream& operator<<(std::ostream& fot, TANXL_DataBase& Taxnl_Data);//用于直接输出当前Item单例内的信息
};

namespace TanxlDB
{
	std::string Combine_Char(std::string data, int Start, int End);//拆分char数组获取指定内容，Start为开始位置End为结束位置(结束位置不保留)

	std::string Divid_Char(std::string data, int Mode = GET_STATUS_DAT);//拆分单行内容获取信息

	void Reset_Chain(TANXL_DataBase& TDB, int Type, int Exac, int Nums);//重置链表某一单元 Nums表示A,B level下的第几个(从0开始)

	void Data(bool Mode = true, unsigned Length_Each = 5);//测试用默认数据 为true时每次添加的同时还会在屏幕上打印 Length_Each为每个分类数据的长度 总共四个分类

	void Combine_File(std::string FileA, std::string FileB);//将FileA和FileB的内容整合到FileA中 仅限USD格式文件使用
}

#endif