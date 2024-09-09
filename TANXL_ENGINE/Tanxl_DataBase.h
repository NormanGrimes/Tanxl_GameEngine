//_VERSION_2_1_ UPDATE LOG
// LAST_UPDATE 2023-03-08 11:27
// 数据属性链表定位接口改为公开
// 结构体定义移入源文件
// 增加控制异常输出信息的宏
// 添加数据链功能增加切换链操作
// 链式数据生成的数据目的位置改为内存
// 添加链式数据功能增加根据序号切换链的功能

#pragma once

#ifndef _TANXL_DATABASE_
#define _TANXL_DATABASE_

#define _ENABLE_TANXL_DATABASE_CONSOLE_OUTPUT_ 0

#if _ENABLE_TANXL_DATABASE_CONSOLE_OUTPUT_

#define _TANXL_DATABASE_CONSOLE_SORT_OUTPUT_   1
#define _TANXL_DATABASE_CONSOLE_FILE_OUTPUT_   1
#define _TANXL_DATABASE_CONSOLE_ERROR_OUTPUT_  1

#endif

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
	SET_UNIT_IDADAT,
	ADD_UNIT_IDADAT
};

struct Data_Unit
{
	Data_Unit(int Id, std::string Data);

	int _Id;
	std::string _Data;
};

struct Data_Link//数据数据结构V4
{
	explicit Data_Link();
	explicit Data_Link(int Id, std::string Data);
	explicit Data_Link(Data_Unit& Data);
	explicit Data_Link(Data_Link* DataLink);
	void Append_Data(int Id, std::string Data);
	void Append_Data(Data_Unit Data);
	void Append_Data(Data_Link* Data, bool Replace = false);

	std::vector<Data_Unit*> _Data_Units;
};

struct Id_Link//序号数据结构V4
{
	explicit Id_Link(int Type, std::string Type_Name, int Exac, std::string Exac_Name, Data_Link* Data = nullptr);
	void Append_Data_Link(Data_Link* Data);
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

	const std::string _Version{ "2.1" };
	std::vector<Id_Link*>* _Id_Links;
	int _Current_Location;
	//用来判断_Internal_Data中是否有数据
	bool _Is_Instance_Data;
	//借由Id_Link_Locate函数对不同深度的Data_Chain定位
	Data_Unit* Data_Link_Locate(int Type, int Exac, int Depth);
	void Replace_Link(int OldType, int OldExac, int OldDepth, int Id, std::string Data);//转移Data_Chain到另一个Id_Chain下
	//↓添加内部数据结构的内容到内存里的Vector中
	void Append_Link(Id_Link& New_Id);
	//↓重置Item结构的内容
	void ResetInstance(bool Delete = false);
	inline void OstreamSpace(std::ostream& os, int Before = 0, int After = 0);//根据级别输出空格 Before用于执行前对级别数值进行修改 After用于执行后
public:
	TANXL_DataBase();//构造函数
	//↓时间复杂度为logN的Id_Link快速定位函数 Type Exac 指Id_Link的同名变量
	Id_Link* Id_Link_Locate(int Type, int Exac);
	//↓获取本地数据 并新建一个链表 支持打开任意格式的文件(.usd .sd)
	bool Get_LocalData(std::string File_Name);
	//↓编辑实例 0x1122 11代表Type位 22代表Exac位 Type_Name为Type字符串 Exac_Name为Exac字符串
	void Set_Internal_Id(unsigned Status, std::string Type_Name, std::string Exac_Name);
	//↓为当前内存中的匿名结构体通过 Set_Mode 的方式添加 Data_Link数据
	void Set_Internal_Data(Data_Link* Data, ELinkSet_Mode Set_Mode);
	//↓读取指定Type(A)_Exac(B)级别的物品 并载入到单例结构中 Depth表示该级别下的第几个物品(从0开始)
	Data_Unit* Get_Specified(int Type, int Exac, int Depth);
	//↓修改指定Type(A)_Exac(B)级别的物品 Nums表示链表中的第几个(从0开始) level取值范围为1~5 用于选定Type Exac Oth1 ...
	//↓修改OTH1 OTH2 OTH3的时候直接更改相关内容 修改TYPE-EXAC时 会转移当前Data_Chain到新的符合修改后的TYPE-EXAC的Id_Chain下
	void Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data);
	//↓删除某一节点与其下所有内容 Type Exac分别用于定位节点的对应级别
	void Remove_Link(int Type, int Exac);
	//↓输出当前内存中的链表的所有内容 支持输出结构中的完整内容 当前内存为空时会抛出错误
	void Print_Data();
	//↓向本地文件中(.usd)添加Item物品 此函数会导致Item单例重置 File_Name指定文件名称 不需要添加后缀 Delete_After为true时会在完成添加后清理结构体
	//↓Mode包括添加信息到内存APPENDTO_MEMO 添加信息到本地文件APPENDTO_FILE 和两边同时添加APPENDTO_BOTH
	void AppendItem(EAppendItem_Mode Mode, std::string File_Name = "Tanxl_Data", bool Delete_After = false);
	//↓使本地(.usd)文件的内容合理化 In_File_Name为输入文件名 Out_File_Name为输出文件名 现在具有保存链表修改功能
	//↓Delete_After_Sort为true时 在数据处理完成之后会删除处理前的原文件 为false则不会删除
	void SortDataBase(ESort_Mode Mode = SORT_LOCALF, std::string Out_File_Name = "Tanxl_Data", std::string In_File_Name = "Tanxl_Data",bool Delete_After_Sort = false);
	//↓添加数据链 Data为需要添加的数据 Divide仅需一次设置 用于标记第几个数据后切换到下一个数据单元 Type指定输入到的Type编号
	void Append_DataChain(std::string Data, unsigned Divide = 0, unsigned Type = 0x01);
	//↓获取当前存储模块的版本信息
	const std::string Get_Version();
	friend std::ostream& operator<<(std::ostream& fot, TANXL_DataBase& Taxnl_Data);//用于直接输出当前Item单例内的信息
};

namespace TanxlDB
{
	std::string Combine_Char(std::string data, int Start, int End);//拆分char数组获取指定内容，Start为开始位置End为结束位置(结束位置不保留)

	std::string Divid_Char(std::string data, int Mode = GET_STATUS_DAT);//拆分单行内容获取信息

	void Reset_Chain(TANXL_DataBase& TDB, int Type, int Exac, int Nums);//重置链表某一单元 Nums表示A,B level下的第几个(从0开始)

	void Combine_File(std::string FileA, std::string FileB);//将FileA和FileB的内容整合到FileA中 仅限USD格式文件使用
}

#endif