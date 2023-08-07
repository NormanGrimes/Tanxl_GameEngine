#pragma once

#include "Tanxl_DataBase.h"

namespace TanxlDB
{
	std::string Combine_Char(std::string data, int Start, int End)
	{
		if (End < Start)
		{
			throw "错误 : Combine_Char 的输入值Start大于End的值";
			return "";
		}
		std::string New_data{};
		for (int i = Start, j = 0; i < End; ++i, ++j)
		{
			if (data[i] == '\t' || data[i] == '<')
			{
				End++; j--;
				continue;
			}
			if (j < 0)j = 0;
			New_data = New_data + data[i];
		}
		return New_data;
	}

	std::string Divid_Char(std::string data, int Mode)
	{
		int Lock{ -1 }, Last{ -1 };
		char Left, Right;
		switch (Mode)
		{
		case GET_STATUS_DAT://获取单例数据0~15
			Left = '/'; Right = '>';
			break;
		case GET_STORAG_DAT://获取储存的信息
			Left = '>'; Right = '<';
			break;
		case GET_STATUS_TAG://信息条目
			Left = '<'; Right = ':';
			break;
		case GET_STATUS_STR://V3链表主副键String
			Left = ':'; Right = '/';
			break;
		case GET_OLDSTY_DAT:
			Left = ':'; Right = '>';
			break;
		default:
			throw "错误 : Divid_Char 没有此条目的功能(0~4 为合法内容，而你输入了" + std::to_string(Mode) + ")";
			return "";
		}
		for (int i = 0; i < data.length(); ++i)//获取内容
		{
			if ((data[i] == Left && Lock == -1) || (data[i] == Right && Lock != -1))
			{
				if (Lock == -1)
				{
					Lock = i + 1;
					continue;
				}
				else
					Last = i;
			}
			if (Lock != -1 && Last != -1)
				return Combine_Char(data, Lock, Last);
		}
		throw "失败 : Divid_Char 读取错误 不存在满足条件的内容";
		return "";
	}

	void Reset_Chain(TANXL_DataBase& TDB, int A, int B, int Nums)
	{
		/*TDB.Set_Specified(A, B, Nums, 3, -1, "NULL");
		TDB.Set_Specified(A, B, Nums, 4, -1, "NULL");
		TDB.Set_Specified(A, B, Nums, 5, -1, "NULL");*/
	}

	void Data(bool Mode, unsigned Length_Each)
	{
		TANXL_DataBase TDB_Instance;
		remove("Tanxl_DataBase.usd");
		for (unsigned Content = (0x11112000 - Length_Each); Content != 0x11112000; ++Content)
		{
			//TDB_Instance.Set_Instance(0x10000000 | 0x0fffffff, "手枪");
			//TDB_Instance.Set_Instance((Content & 0x0f000000) | 0xf0ffffff, "地下水");
			//TDB_Instance.Set_Instance((Content & 0x00ff0000) | 0xff00ffff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance((Content & 0x0000ff00) | 0xffff00ff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance((Content & 0x000000ff) | 0xffffff00, std::to_string(rand() % 100));
			if (Mode)std::cout << TDB_Instance;
			//TDB_Instance.AppendItem();
		}
		for (unsigned Content = 0x22222000 - Length_Each; Content != 0x22222000; ++Content)
		{
			//TDB_Instance.Set_Instance(0x20000000 | 0x0fffffff, "步枪");
			//TDB_Instance.Set_Instance(Content & 0x0f000000 | 0xf0ffffff, "M4A1-S");
			//TDB_Instance.Set_Instance(Content & 0x00ff0000 | 0xff00ffff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance(Content & 0x0000ff00 | 0xffff00ff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance(Content & 0x000000ff | 0xffffff00, std::to_string(rand() % 100));
			if (Mode)std::cout << TDB_Instance;
			//TDB_Instance.AppendItem();
		}
		for (unsigned Content = 0x33332000 - Length_Each; Content != 0x33332000; ++Content)
		{
			//TDB_Instance.Set_Instance(0x30000000 | 0x0fffffff, "重型武器");
			//TDB_Instance.Set_Instance(Content & 0x0f000000 | 0xf0ffffff, "Nova");
			//TDB_Instance.Set_Instance(Content & 0x00ff0000 | 0xff00ffff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance(Content & 0x0000ff00 | 0xffff00ff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance(Content & 0x000000ff | 0xffffff00, std::to_string(rand() % 100));
			if (Mode)std::cout << TDB_Instance;
			//TDB_Instance.AppendItem();
		}
		for (unsigned Content = 0x44442000 - Length_Each; Content != 0x44442000; ++Content)
		{
			//TDB_Instance.Set_Instance(0x40000000 | 0x0fffffff, "微型冲锋枪");
			//TDB_Instance.Set_Instance(Content & 0x0f000000 | 0xf0ffffff, "MP9");
			//TDB_Instance.Set_Instance(Content & 0x00ff0000 | 0xff00ffff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance(Content & 0x0000ff00 | 0xffff00ff, std::to_string(rand() % 100));
			//TDB_Instance.Set_Instance(Content & 0x000000ff | 0xffffff00, std::to_string(rand() % 100));
			if (Mode)std::cout << TDB_Instance;
			//TDB_Instance.AppendItem();
		}
	}

	void Combine_File(std::string FileA, std::string FileB)
	{
		std::string Line{};
		std::fstream in(FileB + ".usd", std::ios::in);
		if (!in.is_open())
			std::fstream in(FileB + ".sd", std::ios::in);
		std::fstream out(FileA + ".sd", std::ios::app);
		if (in.is_open() && out.is_open())
		{
			out << std::endl;
			while (std::getline(in, Line))
				out << Line << std::endl;
		}
		else
			throw "失败 : Combine_File 无法打开的指定文件";
	}
}

std::ostream& operator<<(std::ostream& fot, TANXL_DataBase& s)
{
	fot << "<Type_Status : " << (s._Internal_Data._Item_Status & 0xFF00) << " / " << s._Internal_Data._Type_Name << ">" << std::endl;
	s.OstreamSpace(fot, 1); fot << "<Exac_Status : " << (s._Internal_Data._Item_Status & 0x00FF) << " / " << s._Internal_Data._Exac_Name << ">" << std::endl;
	s.OstreamSpace(fot, 1, 1); fot << "<TDBS_Item>" << std::endl;
	for (int i = 0; i < s._Internal_Data._Data->_Data_Units.size(); i++)
	{
		if (s._Internal_Data._Data->_Data_Units.at(i)._Id)
		{
			s.OstreamSpace(fot);
			fot << "<Data: " << s._Internal_Data._Data->_Data_Units.at(i)._Id << ">"
				<< s._Internal_Data._Data->_Data_Units.at(i)._Data << "</Data>" << std::endl;
		}
	}
	s.OstreamSpace(fot, -1); fot << "</TDBS_Item>" << std::endl;
	s.OstreamSpace(fot, -1); fot << "</Exac_Status>" << std::endl;
	s.OstreamSpace(fot, -1); fot << "</Type_Status>" << std::endl;
	return fot;
}

TANXL_DataBase::TANXL_DataBase() :
	Is_Instance_Data(false), Is_Chain_Empty(true), _Id_Links(new std::vector<Id_Link*>),Current_Location(0) {}

inline void TANXL_DataBase::OstreamSpace(std::ostream& os, int Before, int After)
{
	static int TDB_Status = 0;//级别数值 用于记录当前行的Tab数量
	TDB_Status += Before;
	for (int i = 0; i < TDB_Status; ++i)os << "\t";
	TDB_Status += After;
}

inline void TANXL_DataBase::Combine_Status()
{
	Item_Instance.Item_Status = 
		  (Item_Instance.Status_1 << 28)
		+ (Item_Instance.Status_2 << 24)
		+ (Item_Instance.Status_3 << 16)
		+ (Item_Instance.Status_4 << 8 )
		+  Item_Instance.Status_5;
}

void TANXL_DataBase::ResetInstance()
{
	this->_Internal_Data._Item_Status = 0xFFFF;
	this->_Internal_Data._Type_Name = "";
	this->_Internal_Data._Exac_Name = "";
	this->_Internal_Data._Data = nullptr;
}

void TANXL_DataBase::Set_Internal_Id(unsigned Status, std::string Type_Name, std::string Exac_Name)
{
	this->_Internal_Data._Item_Status = Status;
	this->_Internal_Data._Type_Name = Type_Name;
	this->_Internal_Data._Exac_Name = Exac_Name;
}

void TANXL_DataBase::Set_Internal_Data(Data_Link* Data, ELinkSet_Mode Set_Mode)
{
	switch (Set_Mode)
	{
	case SIMPLE_SET:
		this->_Internal_Data._Data = Data;
		break;
	case APPEND_CUR:
		this->_Internal_Data._Data->Append_Data(Data);
		break;
	case APPEND_TAK:
		if (this->_Internal_Data._Data != nullptr)
		{
			this->_Internal_Data._Data->Append_Data(Data, true);
		}
		break;
	}
}

void TANXL_DataBase::AppendItem(EAppendItem_Mode Mode, std::string File_Name)
{
	if (this->_Internal_Data._Data == nullptr)
	{
		throw "添加失败！内部不完整的数据 : Incomplete data in Internal_Data";
		return;
	}

	if ((Mode == APPENDTO_FILE) || (Mode == APPENDTO_BOTH))
	{
		std::fstream out(File_Name + ".usd", std::ios::app);
		if (out.is_open())
		{
			out << *this;
			out.close();
		}
	}
	if ((Mode == APPENDTO_MEMO) || (Mode == APPENDTO_BOTH))
	{
		Data_Link* DaLink = new Data_Link(
			this->_Internal_Data._Data
		);
		Id_Link* IdLink = new Id_Link(
			this->_Internal_Data._Item_Status & 0xff00, this->_Internal_Data._Type_Name,
			this->_Internal_Data._Item_Status & 0x00ff, this->_Internal_Data._Exac_Name
		);
		this->ResetInstance();
		if (DaLink && IdLink)//判断是否申请空间成功//UNFINISH YET
			Append_Link(*IdLink, *DaLink);
		else
			throw "添加失败！ 申请内存空间失败";
	}
}

/*void TANXL_DataBase::SortDataBase(int Mode, std::string Out_File_Name, std::string In_File_Name, bool Delete_After_Sort)//即将弃用
{
	if (Mode == SORT_LOCALF || Mode == FILE_UNITED)
		if (!Get_LocalData(In_File_Name))
		{
			throw "SortDataBase() Failed ！ : 未能成功匹配文件";
			return;
		}
	if (Is_Chain_Empty)
	{
		throw "SortDataBase() Failed ！ : 获取到的数据为空";
		return;
	}
	std::fstream out(Out_File_Name + ".sd", std::ios::out | std::ios::trunc);
	Id_Vector* PIC{ this->IC_Vector->at(0) };
	out << "<Tanxl_DataBase Information>" << std::endl;
	std::vector<Id_Vector*>::iterator IOIE{ IC_Vector->end() };
	std::vector<Id_Vector*>::iterator IOIB{ IC_Vector->begin() };
	do
	{
		std::vector<Data_Vector*>::iterator IODE{ (*IOIB)->exac->end() };
		std::vector<Data_Vector*>::iterator IODB{ (*IOIB)->exac->begin() };
		std::cout << "\t<Type_Status : " << (*IOIB)->StrA << " / " << (*IOIB)->Type << ">" << std::endl;
		std::cout << "\t\t<Exac_Status : " << (*IOIB)->StrB << " / " << (*IOIB)->Exac << ">" << std::endl;
		out << "\t<Type_Status : " << (*IOIB)->StrA << " / " << (*IOIB)->Type << ">" << std::endl;
		out << "\t\t<Exac_Status : " << (*IOIB)->StrB << " / " << (*IOIB)->Exac << ">" << std::endl;
		do
		{
			std::string TAG = DataTag((*IOIB)->Type, (*IOIB)->Exac, (*IODB)->Id_1);
			std::string TAG_OTH1 = TAG == "" ? "OTH1" : TAG;
			TAG = DataTag((*IOIB)->Type, (*IOIB)->Exac, (*IODB)->Id_2);
			std::string TAG_OTH2 = TAG == "" ? "OTH2" : TAG;
			TAG = DataTag((*IOIB)->Type, (*IOIB)->Exac, (*IODB)->Id_3);
			std::string TAG_OTH3 = TAG == "" ? "OTH3" : TAG;
			if ((*IODB)->Id_1 + (*IODB)->Id_2 + (*IODB)->Id_3 == -3)
				continue;
			if (Mode ^ 0x1)
				out << "\t\t\t<TDB_Item>" << std::endl;
			if ((*IODB)->Id_1 != 0xFF)
			{
				if (Mode ^ 0x1)out << "\t";
				out << "\t\t\t<" + TAG_OTH1 + ": " << (*IODB)->Id_1 << ">" << (*IODB)->Sd_1 << "</" + TAG_OTH1 +">" << std::endl;
			}
			if ((*IODB)->Id_2 != 0xFF)
			{
				if (Mode ^ 0x1)out << "\t";
				out << "\t\t\t<" + TAG_OTH2 + ": " << (*IODB)->Id_2 << ">" << (*IODB)->Sd_2 << "</" + TAG_OTH2 + ">" << std::endl;
			}
			if ((*IODB)->Id_3 != 0xFF)
			{
				if (Mode ^ 0x1)out << "\t";
				out << "\t\t\t<" + TAG_OTH3 + ": " << (*IODB)->Id_3 << ">" << (*IODB)->Sd_3 << "</" + TAG_OTH3 + ">" << std::endl;
			}
			if (Mode ^ 0x1)
				out << "\t\t\t</TDB_Item>" << std::endl;
			++IODB;
		} while (IODB != IODE);
		out << "\t\t</Exac_Status>" << std::endl;
		out << "\t</Type_Status>" << std::endl;
		++IOIB;
	} while (IOIB != IOIE);
	out << "</Tanxl_DataBase Information>" << std::endl;
	out.close();
	for (int i = 0; i < _Id_Links->size(); ++i)
		Remove_Link(_Id_Links->at(i)->_Type, _Id_Links->at(i)->_Exac);
	Is_Chain_Empty = true;
	if (Delete_After_Sort)
	{
		if (Mode == SORT_LOCALF || Mode == FILE_UNITED)
		{
			std::string s = In_File_Name + ".usd";
			remove(s.c_str());
		}
	}
}*/

void TANXL_DataBase::Append_Link(Id_Link& New_Id, Data_Link& New_Data)
{
	if (Is_Chain_Empty)
	{
		this->_Id_Links->push_back(&New_Id);
		this->_Id_Links->at(0)->Append_Data_Link(&New_Data);
		Is_Chain_Empty = false;
		return;
	}
	int Left{ 0 }, Value{ New_Id._Type * 16 * 16 + New_Id._Exac },
		Right{ static_cast<int>(this->_Id_Links->size()) - 1 <= 0 ? 0 : static_cast<int>(this->_Id_Links->size()) - 1 };
	while (true)
	{
		int Mid{ (Left + Right) / 2 };
		Id_Link* PIC = this->_Id_Links->at(Mid);
		int PIC_Value{ PIC->_Type * 16 *16 + PIC->_Exac };
		if (PIC_Value == Value)//Type B匹配时
		{
			PIC->_Data->Append_Data(&New_Data);
			Is_Chain_Empty = false;
			return;
		}
		else if (Left == Right && PIC_Value != Value)//Type B不匹配 但已经是最接近的值时
		{
			if (PIC_Value < Value)
				Left += 1;
			this->_Id_Links->insert(this->_Id_Links->begin() + Left, &New_Id);
			this->_Id_Links->at(Left)->Append_Data_Link(&New_Data);
			Is_Chain_Empty = false;
			return;
		}
		else if (PIC_Value < Value)
			Left = Mid;
		else if (PIC_Value > Value)
			Right = Mid;
		if (Left + 1 == Right)
		{
			if (PIC_Value < Value)
				Left = Right;
			else Right = Left;
		}
	}
	throw "Append_Link() Failed ! : 未知原因";
	return;
}

bool TANXL_DataBase::Get_LocalData(std::string File_Name)
{
	std::fstream in(File_Name + ".usd", std::ios::in);
	if (!in.is_open())
		std::fstream in(File_Name + ".sd", std::ios::in);
	if (in.is_open())
	{
		std::string Type_Data{}, Exac_Data{},Data;//需要使用时再定义
		int  Type_Stat{}, Exac_Stat{},Id;
		Data_Link DTL;
		std::string SData[3]{};
		std::string Line{};
		while (std::getline(in, Line))
		{
			std::string Tag{ TanxlDB::Combine_Char(Line, 1, 5) };
			if (Tag == "Type")
			{
				try
				{
					Type_Stat = std::stoi(TanxlDB::Divid_Char(Line, GET_STATUS_DAT));
					Type_Data = TanxlDB::Divid_Char(Line, GET_STATUS_STR);
					std::getline(in, Line);
					Exac_Stat = std::stoi(TanxlDB::Divid_Char(Line, GET_STATUS_DAT));
					Exac_Data = TanxlDB::Divid_Char(Line, GET_STATUS_STR);
				}
				catch (std::invalid_argument&)
				{
					std::cout << "Invalid argument :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
					Type_Stat = 0;
					Exac_Stat = 0;
				}
				catch (std::out_of_range&)
				{
					std::cout << "Out of range :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
					Type_Stat = 0;
					Exac_Stat = 0;
				}
				while (std::getline(in, Line))
				{
					Tag = TanxlDB::Combine_Char(Line, 1, 5);
					if (Tag == "Type")
					{
						try
						{
							Type_Stat = std::stoi(TanxlDB::Divid_Char(Line, GET_STATUS_DAT));
						}
						catch (std::invalid_argument&)
						{
							std::cout << "Invalid argument :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
							Type_Stat = 0;
						}
						catch (std::out_of_range&)
						{
							std::cout << "Out of range :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
							Type_Stat = 0;
						}
						Type_Data = TanxlDB::Divid_Char(Line, GET_STATUS_STR);
					}
					else if (Tag == "Exac")
					{
						try
						{
							Exac_Stat = std::stoi(TanxlDB::Divid_Char(Line, GET_STATUS_DAT));
						}
						catch (std::invalid_argument&)
						{
							std::cout << "Invalid argument :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
							Exac_Stat = 0;
						}
						catch (std::out_of_range&)
						{
							std::cout << "Out of range :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
							Exac_Stat = 0;
						}
						Exac_Data = TanxlDB::Divid_Char(Line, GET_STATUS_STR);
					}
					else if (Tag == "/TDB")
					{
						Id_Link* Id_Temp = new Id_Link(Type_Stat, Type_Data, Exac_Stat, Exac_Data, &DTL);
						if (Id_Temp)
							Append_Link(*Id_Temp, DTL);
						else
							throw "添加失败！ 申请内存空间失败";
						continue;
					}
					else if (Tag == "Data")
					{
						try
						{
							Id = std::stoi(TanxlDB::Divid_Char(Line, GET_OLDSTY_DAT));
						}
						catch (std::invalid_argument&)
						{
							std::cout << "Invalid argument :" << TanxlDB::Divid_Char(Line, GET_OLDSTY_DAT) << ", Reset to zero" << std::endl;
							Id = 0xFF;
						}
						catch (std::out_of_range&)
						{
							std::cout << "Out of range :" << TanxlDB::Divid_Char(Line, GET_OLDSTY_DAT) << ", Reset to zero" << std::endl;
							Id = 0xFF;
						}
						Data = TanxlDB::Divid_Char(Line, GET_STORAG_DAT);
						DTL.Append_Data(Data_Unit(Id, Data));
					}
				}
			}
		}
		in.close();
		return true;
	}
	else
		return false;
}

/*void TANXL_DataBase::Get_Specified(int Type, int Exac, int Nums)
{
	if (Data_Vector * PDC{ Data_Chain_Locate(Type, Exac, Nums) })
	{
		Id_Vector* PIC = { Id_Chain_Locate(Type, Exac) };
		Item_Instance.Status_1 = PIC->Type;  Item_Instance.Code = PIC->StrA;
		Item_Instance.Status_2 = PIC->Exac;  Item_Instance.Name = PIC->StrB;
		Item_Instance.Status_3 = PDC->Id_1;  Item_Instance.Oth1 = PDC->Sd_1;
		Item_Instance.Status_4 = PDC->Id_2;  Item_Instance.Oth2 = PDC->Sd_2;
		Item_Instance.Status_5 = PDC->Id_3;  Item_Instance.Oth3 = PDC->Sd_3;
		Combine_Status();
		return;
	}
	throw "Get_Specified() Failed ！ : 未能成功匹配相同值";
}*/

void TANXL_DataBase::Get_Item_Status()
{
	Item_Instance.Status_1 = ((Item_Instance.Item_Status & 0xf0000000) >> 28);
	Item_Instance.Status_2 = ((Item_Instance.Item_Status & 0x0f000000) >> 24);
	Item_Instance.Status_3 = ((Item_Instance.Item_Status & 0x00ff0000) >> 16);
	Item_Instance.Status_4 = ((Item_Instance.Item_Status & 0x0000ff00) >>  8);
	Item_Instance.Status_5 = ( Item_Instance.Item_Status & 0x000000ff       );
}

void TANXL_DataBase::Print_Data()
{
	std::vector<Id_Link*>::iterator BOI{ (this->_Id_Links->begin()) };
	std::vector<Id_Link*>::iterator EOI{ (this->_Id_Links->end() - 1) };
	while (true)
	{
		std::cout << "Id_Link :" << (*BOI)->_Type << " - " << (*BOI)->_Type_Name << " - " << (*BOI)->_Exac << " - " << (*BOI)->_Exac_Name << std::endl;
		Data_Link* DL{ ((*BOI)->_Data) };
		for (int i = 0; i < DL->_Data_Units.size(); ++i)
			std::cout << "\tData_Link :" << DL->_Data_Units.at(i)._Id << " - " << DL->_Data_Units.at(i)._Data << std::endl;
		if (BOI == EOI)
			break;
		BOI++;
	} 
}

/*void TANXL_DataBase::Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data) //V3 Updated
{
	if (Data_Link * PDC{ Data_Link_Locate(Type, Exac, Nums) })
		switch (level)
		{
		case SET_TYPE_STATUS:
			Replace_Chain(Type, Exac, Nums, Id, Exac);
			return;
		case SET_EXAC_STATUS:
			Replace_Chain(Type, Exac, Nums, Type, Id);
			return;
		case SET_OTH1_STATUS:
			PDC->Id_1 = Id;
			PDC->Sd_1 = Data;
			return;
		case SET_OTH2_STATUS:
			PDC->Id_2 = Id;
			PDC->Sd_2 = Data;
			return;
		case SET_OTH3_STATUS:
			PDC->Id_3 = Id;
			PDC->Sd_3 = Data;
			return;
		}
	throw "Set_Specified() Failed ！ : 查找相关内容不成功或链表内容为空";
}*/

void TANXL_DataBase::Remove_Link(int Type, int Exac)
{
	if (Id_Link * PIC{ Id_Link_Locate(Type, Exac) })
	{
		delete PIC->_Data;
		delete PIC;
		_Id_Links->erase(_Id_Links->begin() + Current_Location);
	}
}

Id_Link* TANXL_DataBase::Id_Link_Locate(int Type, int Exac)
{
	int Left{ 0 }, Value{ Type * 16 + Exac },
		Right{ static_cast<int>(this->_Id_Links->size()) - 1 >= 0 ? static_cast<int>(this->_Id_Links->size()) - 1 : 0 };;
	if (Left == Right)
	{
		if (Value == this->_Id_Links->at(0)->_Type * 16 + this->_Id_Links->at(0)->_Exac)
		{
			Current_Location = 0;
			return this->_Id_Links->at(0);
		}
		throw "Id_Chain_Locate Failed ! : 未能成功匹配相同值";
		return nullptr;
	}
	else
	{
		while (Left != Right)
		{
			int Mid{ (Left + Right) / 2 };
			int Mid_Value{ this->_Id_Links->at(Mid)->_Type * 16 + this->_Id_Links->at(Mid)->_Exac };
			if (Mid_Value == Value)
			{
				Current_Location = Mid;
				return this->_Id_Links->at(Mid);
			}
			else if (Mid_Value > Value)
				Right = Mid;
			else if (Mid_Value < Value)
				Left = Mid;
			if (Left == Right)
			{
				throw "Id_Chain_Locate Failed ! : 未能成功匹配相同值";
				return nullptr;
			}
		}
	}
	throw "Id_Chain_Locate Failed ! : 未知原因";
	return nullptr;
}

Data_Unit* TANXL_DataBase::Data_Link_Locate(int Type, int Exac, int Depth)
{
	Id_Link* PIC{ Id_Link_Locate(Type, Exac) };
	if (PIC->_Data->_Data_Units.size() < Depth)
	{
		throw "Data_Link_Locate Failed ! : 超出当前容器最大深度";
		return nullptr;
	}
	else if (Depth < 0 && Depth + static_cast<int>(PIC->_Data->_Data_Units.size()) >= 0)
		return &(PIC->_Data->_Data_Units.at(Depth + PIC->_Data->_Data_Units.size()));
	while (Depth + static_cast<int>(PIC->_Data->_Data_Units.size() < 0))
		Depth += static_cast<int>(PIC->_Data->_Data_Units.size());
	return &(PIC->_Data->_Data_Units.at(Depth));
}

void TANXL_DataBase::Replace_Link(int OldType, int OldExac, int OldDepth, int Type, int Exac)
{
	Id_Link* PIC{ Id_Link_Locate(OldType, OldExac) };
	//Append_Chain(*PIC->exac->at(OldDepth), *new Id_Vector(Type, Exac));
	if (PIC->_Data->_Data_Units.size() > OldDepth && OldDepth >= 0)
		PIC->_Data->_Data_Units.erase(PIC->_Data->_Data_Units.begin() + OldDepth);
	else if (PIC->_Data->_Data_Units.size() + OldDepth >= 0 && PIC->_Data->_Data_Units.size() + OldDepth < PIC->_Data->_Data_Units.size())
		PIC->_Data->_Data_Units.erase(PIC->_Data->_Data_Units.begin() + PIC->_Data->_Data_Units.size() + OldDepth);
}

const std::string TANXL_DataBase::Get_Version()
{
	return this->_Version;
}