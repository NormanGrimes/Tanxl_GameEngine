//_VERSION_2_0+_ UPDATE LOG
// LAST_UPDATE 2023-02-13 15:11
// V4_UPDATE 增加第四版替换物品功能
// 移除组合物品等级接口
// 移除第三版内部匿名结构体
// V4_UPDATE 增加第四版指定获取功能
// 移除获取物品等级功能
// V4_UPDATE 增加第四版设置指定功能
// V4_UPDATE 增加第四版数据整理功能
// 修复数据打印空指针未处理的问题
// 修复输出重载的输出顺序错误的问题
// 修复SIMPLE_SET未析构丢弃内容的问题
// 匿名结构体重置函数可选是否析构其指针所指内容
// 修复匿名结构体的取代功能会在本身指针为空时失效的问题
// 添加物品功能可选是否添加完成后删除
// 添加序号结构体的函数不再需要输入数据结构体
// 修复数据结构体添加数据可能造成无限循环的问题
// 移除内存中数据是否为空的标记
// 多处细节改进与小问题修复
// 改进本地文件读取功能
// 针对内存部分进行优化
// 增加一个简化步骤的数据添加接口
// 恢复重置指定数据的功能
// 变量名称对应最新版本进行修改
// 获取本地数据接口的内存清理步骤优化
// 数据整理功能将联合整理设为默认并取代旧式整理

#pragma once

#ifndef _TANXL_DATABASE_
#define _TANXL_DATABASE_

#include<iostream>
#include<fstream>
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
	SORT_MEMORY
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
	SET_UNIT_IDADAT
};

struct Data_Unit
{
	Data_Unit(int Id, std::string Data) :_Id(Id), _Data(Data) {}

	int _Id;
	std::string _Data;
};

struct Data_Link//数据数据结构V4
{
	explicit Data_Link() :_Data_Units() {}
	explicit Data_Link(int Id, std::string Data)
	{
		_Data_Units.push_back(new Data_Unit(Id, Data));
	}
	explicit Data_Link(Data_Unit& Data)
	{
		_Data_Units.push_back(&Data);
	}
	explicit Data_Link(Data_Link* DataLink)
	{
		this->_Data_Units = DataLink->_Data_Units;
	}
	void Append_Data(int Id, std::string Data)
	{
		_Data_Units.push_back(new Data_Unit(Id, Data));
	}
	void Append_Data(Data_Unit Data)
	{
		_Data_Units.push_back(&Data);
	}
	void Append_Data(Data_Link* Data, bool Replace = false)
	{
		if (Data == nullptr)
			return;
		if (Replace)
			std::vector<Data_Unit*>().swap(this->_Data_Units);
		int TempVal = static_cast<int>(Data->_Data_Units.size());
		for (int i = 0; i < TempVal; ++i)//防止自己给自己添加造成无限循环
			this->_Data_Units.push_back(Data->_Data_Units.at(i));
	}

	std::vector<Data_Unit*> _Data_Units;
};

struct Id_Link//序号数据结构V4
{
	explicit Id_Link(int Type, std::string Type_Name, int Exac, std::string Exac_Name, Data_Link* Data = nullptr) :
		_Type(Type), _Type_Name(Type_Name), _Exac(Exac), _Exac_Name(Exac_Name)
	{
		_Data = new Data_Link;
		_Data->Append_Data(Data);
	}
	void Append_Data_Link(Data_Link* Data)
	{
		if (_Data == nullptr)
			_Data = new Data_Link(Data);
		else
			_Data->Append_Data(Data);
	}
	int _Type, _Exac;
	std::string _Type_Name, _Exac_Name;
	Data_Link* _Data;
};

class TANXL_DataBase
{
private:
	struct
	{
		unsigned int _Item_Status{ 0xFFFF };//Type 8位 Exac 8位
		std::string _Type_Name{ "" };
		std::string _Exac_Name{ "" };
		Data_Link* _Data{ nullptr };
	}_Internal_Data;

	const std::string _Version{ "2.0+" };
	std::vector<Id_Link*>* _Id_Links;
	int Current_Location;
	bool Is_Instance_Data;//用来判断Item_Instance中是否有数据
	//↓时间复杂度为logN的Id_Chain快速定位函数 Type Exac 指Id_Link的同名变量
	Id_Link* Id_Link_Locate(int Type, int Exac);
	//借由Id_Link_Locate函数对不同深度的Data_Chain定位
	Data_Unit* Data_Link_Locate(int Type, int Exac, int Depth);
	void Replace_Link(int OldType, int OldExac, int OldDepth, int Id, std::string Data);//转移Data_Chain到另一个Id_Chain下
	//↓添加内部数据结构的内容到内存里的Vector中 V4
	void Append_Link(Id_Link& New_Id);
	//↓重置Item结构的内容
	void ResetInstance(bool Delete = false);
	inline void OstreamSpace(std::ostream& os, int Before = 0, int After = 0);//根据级别输出空格 Before用于执行前对级别数值进行修改 After用于执行后
public:
	TANXL_DataBase();//构造函数
	bool Get_LocalData(std::string File_Name);//获取本地数据 并新建一个链表 支持打开任意格式的文件(.usd .sd)
	//↓编辑实例 0x1122 11代表Type位 22代表Exac位 Type_Name为Type字符串 Exac_Name为Exac字符串
	void Set_Internal_Id(unsigned Status, std::string Type_Name, std::string Exac_Name);
	//↓为当前内存中的匿名结构体通过 Set_Mode 的方式添加 Data_Link数据
	void Set_Internal_Data(Data_Link* Data, ELinkSet_Mode Set_Mode);
	//↓读取指定Type(A)_Exac(B)级别的物品 并载入到单例结构中 Depth表示该级别下的第几个物品(从0开始)
	void Get_Specified(int Type, int Exac, int Depth);
	//↓修改指定Type(A)_Exac(B)级别的物品 Nums表示链表中的第几个(从0开始) level取值范围为1~5 用于选定Type Exac Oth1 ...
	//↓修改OTH1 OTH2 OTH3的时候直接更改相关内容 修改TYPE-EXAC时 会转移当前Data_Chain到新的符合修改后的TYPE-EXAC的Id_Chain下
	void Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data);
	//↓删除某一节点与其下所有内容
	void Remove_Link(int Type, int Exac);
	//↓输出当前内存中的链表的所有内容 支持输出结构中的完整内容 当前内存为空时会抛出错误
	void Print_Data();
	//↓向本地文件中(.usd)添加Item物品 此函数会导致Item单例重置 To_File为true时会向文件输出 否则存储到内存中 File_Name指定文件名称 不需要添加后缀 Keep_Instance可在为true时 完成添加后不清理Instance数据
	void AppendItem(EAppendItem_Mode Mode, std::string File_Name = "Tanxl_Data", bool Delete_After = false);
	//↓使本地(.usd)文件的内容合理化 In_File_Name为输入文件名 Out_File_Name为输出文件名 现在具有保存链表修改功能
	//↓Delete_After_Sort为true时 在数据处理完成之后会删除处理前的原文件 为false则不会删除
	void SortDataBase(ESort_Mode Mode = SORT_LOCALF, std::string Out_File_Name = "Tanxl_Data", std::string In_File_Name = "Tanxl_Data",bool Delete_After_Sort = false);
	//↓获取当前存储模块的版本信息
	void Append_DataChain(std::string Data, unsigned Divide = 0);//添加数据链 TDB指定添加的目标 Data为需要添加的数据 Divide仅需一次设置 用于标记第几个数据后切换到下一个数据单元
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