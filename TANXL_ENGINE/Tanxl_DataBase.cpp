#pragma once

#include "Tanxl_DataBase.h"

Data_Unit::Data_Unit(int Id, std::string Data) :_Id(Id), _Data(Data) {}

Data_Link::Data_Link() :_Data_Units() {}

Data_Link::Data_Link(int Id, std::string Data)
{
	_Data_Units.push_back(new Data_Unit(Id, Data));
}

Data_Link::Data_Link(Data_Unit& Data)
{
	_Data_Units.push_back(&Data);
}

Data_Link::Data_Link(Data_Link* DataLink)
{
	this->_Data_Units = DataLink->_Data_Units;
}

void Data_Link::Append_Data(int Id, std::string Data)
{
	_Data_Units.push_back(new Data_Unit(Id, Data));
}
void Data_Link::Append_Data(Data_Unit Data)
{
	_Data_Units.push_back(&Data);
}
void Data_Link::Append_Data(Data_Link* Data, bool Replace)
{
	if (Data == nullptr)
		return;
	if (Replace)
		std::vector<Data_Unit*>().swap(this->_Data_Units);
	int TempVal{ static_cast<int>(Data->_Data_Units.size()) };
	for (int i{ 0 }; i < TempVal; ++i)//防止自己给自己添加造成无限循环
		this->_Data_Units.push_back(Data->_Data_Units.at(i));
}

Id_Link::Id_Link(int Type, std::string Type_Name, int Exac, std::string Exac_Name, Data_Link* Data) :
	_Type(Type), _Type_Name(Type_Name), _Exac(Exac), _Exac_Name(Exac_Name)
{
	_Data = new Data_Link;
	_Data->Append_Data(Data);
}

void Id_Link::Append_Data_Link(Data_Link* Data)
{
	if (_Data == nullptr)
		_Data = new Data_Link(Data);
	else
		_Data->Append_Data(Data);
}

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
		for (int i{ Start }; i < End; ++i)
		{
			if ((data[i] == '\t') || (data[i] == '<'))
			{
				End++;
				continue;
			}
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
		for (int i{ 0 }; i < data.length(); ++i)//获取内容
		{
			if (((data[i] == Left) && (Lock == -1)) || ((data[i] == Right) && (Lock != -1)))
			{
				if (Lock == -1)
				{
					Lock = i + 1;
					continue;
				}
				else
					Last = i;
			}
			if ((Lock != -1) && (Last != -1))
				return Combine_Char(data, Lock, Last);
		}
		throw "失败 : Divid_Char 读取错误 不存在满足条件的内容";
		return "";
	}

	void Combine_File(std::string FileA, std::string FileB)
	{
		TANXL_DataBase TDB;
		TDB.Get_LocalData(FileA);
		TDB.Get_LocalData(FileB, false);
		TDB.SortDataBase(SORT_MEMORY);
	}
}

std::ostream& operator<<(std::ostream& out, TANXL_DataBase& s)
{
	out << "<Type_Status : " << s._Internal_Data._Type_Name << " / " << ((s._Internal_Data._Item_Status & 0xFFFF0000) >> 16) << ">" << std::endl;
	s.OstreamSpace(out, 1); out << "<Exac_Status : " << s._Internal_Data._Exac_Name << " / " << (s._Internal_Data._Item_Status & 0x0000FFFF) << ">" << std::endl;
	s.OstreamSpace(out, 1, 1); out << "<TDBS_Item>" << std::endl;
	for (int i{ 0 }; i < s._Internal_Data._Data->_Data_Units.size(); ++i)
	{
		s.OstreamSpace(out);
		out << "<Data: " << s._Internal_Data._Data->_Data_Units.at(i)->_Id << ">"
			<< s._Internal_Data._Data->_Data_Units.at(i)->_Data << "</Data>" << std::endl;
	}
	s.OstreamSpace(out, -1); out << "</TDBS_Item>" << std::endl;
	s.OstreamSpace(out, -1); out << "</Exac_Status>" << std::endl;
	s.OstreamSpace(out, -1); out << "</Type_Status>" << std::endl;
	return out;
}

TANXL_DataBase::TANXL_DataBase() :
	_Id_Links(new std::vector<Id_Link*>), _Current_Location(0), Tanxl_ClassBase("2.1") {}

TANXL_DataBase::TANXL_DataBase(std::string File_Name) :
	_Id_Links(new std::vector<Id_Link*>), _Current_Location(0), Tanxl_ClassBase("2.1")
{
	this->Get_LocalData(File_Name);
}

inline void TANXL_DataBase::OstreamSpace(std::ostream& os, int Before, int After)
{
	static int TDB_Status{ 0 };//级别数值 用于记录当前行的Tab数量
	TDB_Status += Before;
	for (int i{ 0 }; i < TDB_Status; ++i)os << "\t";
	TDB_Status += After;
}

void TANXL_DataBase::ResetInstance(bool Delete)
{
	this->_Internal_Data._Item_Status = 0xFFFFFFFF;
	this->_Internal_Data._Type_Name = "";
	this->_Internal_Data._Exac_Name = "";
	if (Delete && (this->_Internal_Data._Data != nullptr))
	{
		std::vector<Data_Unit*>().swap(this->_Internal_Data._Data->_Data_Units);
		delete this->_Internal_Data._Data;
	}
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
		delete this->_Internal_Data._Data;
		this->_Internal_Data._Data = Data;
		break;
	case APPEND_CUR:
		this->_Internal_Data._Data->Append_Data(Data);
		delete Data;
		break;
	case APPEND_TAK:
		this->_Internal_Data._Data->Append_Data(Data, true);
		break;
	}
}

void TANXL_DataBase::AppendItem(EAppendItem_Mode Mode, std::string File_Name, bool Delete_After)
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
		Id_Link* IdLink{ new Id_Link(
			(this->_Internal_Data._Item_Status & 0xFFFF0000) >> 16, this->_Internal_Data._Type_Name,
			this->_Internal_Data._Item_Status & 0x0000FFFF, this->_Internal_Data._Exac_Name,
			new Data_Link(this->_Internal_Data._Data)) };
		if (IdLink)//判断是否申请空间成功//UNFINISH YET
			Append_Link(*IdLink);
		else
			throw "添加失败！ 申请内存空间失败";
	}
	this->ResetInstance(Delete_After);
}

void TANXL_DataBase::SortDataBase(ESort_Mode Mode, std::string Out_File_Name, std::string In_File_Name, bool Delete_After_Sort)
{
	if (Mode == SORT_LOCALF)
		if (!Get_LocalData(In_File_Name))
		{
			throw "SortDataBase() Failed ！ : 未能成功匹配文件";
			return;
		}
	if (this->_Id_Links->size() == 0)
	{
		throw "SortDataBase() Failed ！ : 获取到的数据为空";
		return;
	}
	std::fstream out(Out_File_Name + ".sd", std::ios::out | std::ios::trunc);
	out << "<Tanxl_DataBase Information>" << std::endl;
	std::vector<Id_Link*>::iterator IOIE{ this->_Id_Links->end() };
	std::vector<Id_Link*>::iterator IOIB{ this->_Id_Links->begin() };
	int last{ -1 };
	do
	{
#if _TANXL_DATABASE_CONSOLE_SORT_OUTPUT_
		std::cout << "(*IOIB)" << (*IOIB)->_Data->_Data_Units.size() << std::endl;
#endif
		std::vector<Data_Unit*>::iterator IODE{ (*IOIB)->_Data->_Data_Units.end() };
		std::vector<Data_Unit*>::iterator IODB{ (*IOIB)->_Data->_Data_Units.begin() };
#if _TANXL_DATABASE_CONSOLE_SORT_OUTPUT_
		std::cout << "\t<Type_Status : " << (*IOIB)->_Type_Name << " / " << (*IOIB)->_Type << ">" << std::endl;
		std::cout << "\t\t<Exac_Status : " << (*IOIB)->_Exac_Name << " / " << (*IOIB)->_Exac << ">" << std::endl;
#endif
		if (((*IOIB)->_Type != last) && last != -1)
			out << "\t</Type_Status>" << std::endl;
		if ((*IOIB)->_Type != last)
			out << "\t<Type_Status : " << (*IOIB)->_Type_Name << " / " << (*IOIB)->_Type << ">" << std::endl;
		int Count{ 0 };
		do
		{
			if (Count == 0)
				out << "\t\t<Exac_Status : " << (*IOIB)->_Exac_Name << " / " << (*IOIB)->_Exac << ">" << std::endl;
#if !_ENABLE_TANXL_DATABASE_INDEPENDENT_
			std::string TAG{ DataTag((*IOIB)->_Type, (*IOIB)->_Exac, (*IODB)->_Id) };
			TAG = (TAG == "" ? "DATA" : TAG);
#else
			std::string TAG{ "DATA" };
#endif
			out << "\t\t\t<" + TAG + ": " << (*IODB)->_Id << ">" << (*IODB)->_Data << "</" + TAG + ">" << std::endl;
#if _TANXL_DATABASE_CONSOLE_SORT_OUTPUT_
			std::cout << "\t\t\t<" + TAG + ": " << (*IODB)->_Id << ">" << (*IODB)->_Data << "</" + TAG + ">" << std::endl;
#endif
			++Count;
			++IODB;
		} while (IODB != IODE);
		out << "\t\t</Exac_Status>" << std::endl;
		last = (*IOIB)->_Type;
		++IOIB;
	} while (IOIB != IOIE);
	out << "\t</Type_Status>" << std::endl;
	out << "</Tanxl_DataBase Information>" << std::endl;
	out.close();
	if (Delete_After_Sort && (Mode == SORT_LOCALF))
		remove((In_File_Name + ".usd").c_str());
}

void TANXL_DataBase::Append_Link(Id_Link& New_Id)
{
	if (this->_Id_Links->size() == 0)
	{
		this->_Id_Links->insert(this->_Id_Links->begin(), &New_Id);
		return;
	}
	int Left{ 0 }, Value{ (New_Id._Type << 16) + New_Id._Exac },
		Right{ static_cast<int>(this->_Id_Links->size()) - 1 <= 0 ? 0 : static_cast<int>(this->_Id_Links->size()) - 1 };
	while (true)
	{
		int Mid{ (Left + Right) / 2 };
		Id_Link* PIL{ this->_Id_Links->at(Mid) };
		int PIL_Value{ (PIL->_Type << 16) + PIL->_Exac };
		if (PIL_Value == Value)//Type B匹配时
		{
			PIL->_Data->Append_Data(New_Id._Data);
			return;
		}
		else if ((Left == Right) && (PIL_Value != Value))//Type B不匹配 但已经是最接近的值时
		{
			if (PIL_Value < Value)
				Left += 1;
			this->_Id_Links->insert(this->_Id_Links->begin() + Left, &New_Id);
			return;
		}
		else if (PIL_Value < Value)
			Left = Mid;
		else if (PIL_Value > Value)
			Right = Mid;
		if (Left + 1 == Right)
		{
			if (PIL_Value < Value)
				Left = Right;
			else Right = Left;
		}
	}
	throw "Append_Link() Failed ! : 未知原因";
	return;
}

bool TANXL_DataBase::Get_LocalData(std::string File_Name, bool Clear_Current)
{
	if (Clear_Current)
		std::vector<Id_Link*>().swap(*this->_Id_Links);
	std::fstream in(File_Name + ".usd", std::ios::in);
	if (!in.is_open())
		in.open(File_Name + ".sd", std::ios::in);
	if (in.is_open())
	{
		std::string Type_Data{}, Exac_Data{}, Data{};//需要使用时再定义
		int Type_Stat{}, Exac_Stat{}, Id{};
		Data_Link DTL;
		std::string Line{};
		while (std::getline(in, Line))
		{
#if _TANXL_DATABASE_CONSOLE_FILE_OUTPUT_
			std::cout << Line << std::endl;
#endif
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
#if _TANXL_DATABASE_CONSOLE_ERROR_OUTPUT_
					std::cout << "Type Invalid argument :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
#endif
					Type_Stat = 0;
					Exac_Stat = 0;
				}
				catch (std::out_of_range&)
				{
#if _TANXL_DATABASE_CONSOLE_ERROR_OUTPUT_
					std::cout << "Type Out of range :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
#endif
					Type_Stat = 0;
					Exac_Stat = 0;
				}
			}
			else if (Tag == "Exac")
			{
				try
				{
					Exac_Stat = std::stoi(TanxlDB::Divid_Char(Line, GET_STATUS_DAT));
					Exac_Data = TanxlDB::Divid_Char(Line, GET_STATUS_STR);
				}
				catch (std::invalid_argument&)
				{
#if _TANXL_DATABASE_CONSOLE_ERROR_OUTPUT_
					std::cout << "Exac Invalid argument :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
#endif
					Exac_Stat = 0;
				}
				catch (std::out_of_range&)
				{
#if _TANXL_DATABASE_CONSOLE_ERROR_OUTPUT_
					std::cout << "Exac Out of range :" << TanxlDB::Divid_Char(Line, GET_STATUS_DAT) << ", Reset to zero" << std::endl;
#endif
					Exac_Stat = 0;
				}
			}
			else if ((Tag == "/TDB") || (Tag == "/Exa"))
			{
				Id_Link* Id_Temp{ new Id_Link(Type_Stat, Type_Data, Exac_Stat, Exac_Data, &DTL) };
				std::vector<Data_Unit*>().swap(DTL._Data_Units);//释放内存
				if (Id_Temp)
					Append_Link(*Id_Temp);
				else
					throw "添加失败！ 申请内存空间失败";
				continue;
			}
			else if ((Tag == "UNIQ") || (Tag == "TANX") || (Tag == "DATA"))
			{
				try
				{
					Id = std::stoi(TanxlDB::Divid_Char(Line, GET_OLDSTY_DAT));
				}
				catch (std::invalid_argument&)
				{
#if _TANXL_DATABASE_CONSOLE_ERROR_OUTPUT_
					std::cout << "Id Invalid argument :" << TanxlDB::Divid_Char(Line, GET_OLDSTY_DAT) << ", Reset to zero" << std::endl;
#endif
					Id = 0xFF;
				}
				catch (std::out_of_range&)
				{
#if _TANXL_DATABASE_CONSOLE_ERROR_OUTPUT_
					std::cout << "Id Out of range :" << TanxlDB::Divid_Char(Line, GET_OLDSTY_DAT) << ", Reset to zero" << std::endl;
#endif
					Id = 0xFF;
				}
				Data = TanxlDB::Divid_Char(Line, GET_STORAG_DAT);
				DTL.Append_Data(Id, Data);
			}
		}
		in.close();
		return true;
	}
	else
	{
		in.close();
		return false;
	}
}

void TANXL_DataBase::Print_Data()
{
	std::vector<Id_Link*>::iterator BOI{ this->_Id_Links->begin() };
	std::vector<Id_Link*>::iterator EOI{ this->_Id_Links->end() };
	while (BOI != EOI)
	{
		std::cout << "Id_Link :" << (*BOI)->_Type << " - " << (*BOI)->_Type_Name << " - " << (*BOI)->_Exac << " - " << (*BOI)->_Exac_Name << std::endl;
		Data_Link* DL{ ((*BOI)->_Data) };
		if (DL != nullptr)
			for (int i{ 0 }; i < DL->_Data_Units.size(); ++i)
				std::cout << "\tData_Link :" << DL->_Data_Units.at(i)->_Id << " - " << DL->_Data_Units.at(i)->_Data << std::endl;
		++BOI;
	}
}

void TANXL_DataBase::Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data)
{
	if (Data_Unit * PDU{ Data_Link_Locate(Type, Exac, Nums) })
		switch (level)
		{
		case SET_TYPE_STATUS:
			Replace_Link(Type, Exac, Nums, Id, Data);
			return;
		case SET_EXAC_STATUS:
			Replace_Link(Type, Exac, Nums, Type, Data);
			return;
		case SET_UNIT_IDADAT:
			PDU->_Id = Id;
			PDU->_Data = Data;
			return;
		case ADD_UNIT_IDADAT:
		{
			Id_Link* PIL{ Id_Link_Locate(Type,Exac) };
			PIL->Append_Data_Link(new Data_Link(Id, Data));
			return;
		}
		}
	throw "Set_Specified() Failed ！ : 查找相关内容不成功或链表内容为空";
}

void TANXL_DataBase::Remove_Link(int Type, int Exac)
{
	if (Id_Link * PIL{ Id_Link_Locate(Type, Exac) })
	{
		std::vector<Data_Unit*>().swap(PIL->_Data->_Data_Units);
		delete PIL;
		this->_Id_Links->erase(this->_Id_Links->begin() + this->_Current_Location);
	}
}

Id_Link* TANXL_DataBase::Id_Link_Search(int Level)
{
	if ((Level < 0) && (Level > this->_Id_Links->size()))
		return nullptr;
	return this->_Id_Links->at(Level);
}

Id_Link* TANXL_DataBase::Id_Link_Locate(int Type, int Exac)
{
	int Left{ 0 }, Value{ (Type << 16) + Exac },
		Right{ static_cast<int>(this->_Id_Links->size()) - 1 >= 0 ? static_cast<int>(this->_Id_Links->size()) - 1 : 0 };
	if (Left == Right)
	{
		if (Value == (this->_Id_Links->at(0)->_Type << 16) + this->_Id_Links->at(0)->_Exac)
		{
			this->_Current_Location = 0;
			return this->_Id_Links->at(0);
		}
		throw static_cast<std::string>("Id_Chain_Locate Failed ! : 未能成功匹配相同值");
		return nullptr;
	}
	else
	{
		while (Left != Right)
		{
			int Mid{ (Left + Right) / 2 };
			int Mid_Value{ (this->_Id_Links->at(Mid)->_Type << 16) + this->_Id_Links->at(Mid)->_Exac };
			if (Mid_Value == Value)
			{
				this->_Current_Location = Mid;
				return this->_Id_Links->at(Mid);
			}
			else if (Mid_Value > Value)
				Right = Mid;
			else if (Mid_Value < Value)
				Left = Mid;

			if (Left == Right)
			{
				throw static_cast<std::string>("Id_Chain_Locate Failed ! : 未能成功匹配相同值");
				return nullptr;
			}
			if (Left + 1 == Right)
			{
				if ((this->_Id_Links->at(Right)->_Type << 16) + this->_Id_Links->at(Right)->_Exac == Value)
				{
					this->_Current_Location = Right;
					return this->_Id_Links->at(Right);
				}
				else if ((this->_Id_Links->at(Left)->_Type << 16) + this->_Id_Links->at(Left)->_Exac == Value)
				{
					this->_Current_Location = Left;
					return this->_Id_Links->at(Left);
				}
				//std::cout << "Value : " << Value << std::endl;
				throw static_cast<std::string>("Id_Chain_Locate Failed ! : 未能成功匹配相同值");
				return nullptr;
			}
		}
	}
	throw static_cast<std::string>("Id_Chain_Locate Failed ! : 未知原因");
	return nullptr;
}

Id_Link* TANXL_DataBase::Get_Last_Located(int Check_Type, int Check_Exac, int OffSet)
{
	try
	{
		if ((this->_Id_Links->at(static_cast<size_t>(_Current_Location + OffSet))->_Type == Check_Type) &&
			(this->_Id_Links->at(static_cast<size_t>(_Current_Location + OffSet))->_Exac == Check_Exac))
			return this->_Id_Links->at(static_cast<size_t>(_Current_Location + OffSet));
		return Id_Link_Locate(Check_Type, Check_Exac);
	}
	catch (std::out_of_range&)
	{
		throw static_cast<std::string>("Get_Last_Located Failed ! : 获取上一次定位数据偏置超出范围");
	}
}

Data_Unit* TANXL_DataBase::Data_Link_Locate(int Type, int Exac, int Depth)
{
	Id_Link* PIL{ Id_Link_Locate(Type, Exac) };
	if (PIL->_Data->_Data_Units.size() < Depth)
	{
		throw "Data_Link_Locate Failed ! : 超出当前容器最大深度";
		return nullptr;
	}
	else if (Depth < 0 && Depth + static_cast<int>(PIL->_Data->_Data_Units.size()) >= 0)
		return PIL->_Data->_Data_Units.at(Depth + PIL->_Data->_Data_Units.size());
	while (Depth + static_cast<int>(PIL->_Data->_Data_Units.size()) < 0)
		Depth += static_cast<int>(PIL->_Data->_Data_Units.size());
	return PIL->_Data->_Data_Units.at(Depth);
}

void TANXL_DataBase::Replace_Link(int OldType, int OldExac, int OldDepth, int Id, std::string Data)
{
	Id_Link* PIL{ Id_Link_Locate(OldType, OldExac) };
	PIL->_Data->Append_Data(Id, Data);
	if (PIL->_Data->_Data_Units.size() > OldDepth && OldDepth >= 0)
		PIL->_Data->_Data_Units.erase(PIL->_Data->_Data_Units.begin() + OldDepth);
	else if (PIL->_Data->_Data_Units.size() + OldDepth >= 0 && PIL->_Data->_Data_Units.size() + OldDepth < PIL->_Data->_Data_Units.size())
		PIL->_Data->_Data_Units.erase(PIL->_Data->_Data_Units.begin() + PIL->_Data->_Data_Units.size() + OldDepth);
}

void TANXL_DataBase::Append_DataChain(std::string Data, unsigned Divide, unsigned Type, unsigned Exac)
{
	static int Div{ static_cast<int>(Divide) };
	static int Cur{ 0 };
	if ((Divide != 0) && (Divide != Div))
	{
		Cur = 0;
		Div = Divide;
	}

	static unsigned Chain_Exac{ 0x0000 };
	static unsigned Last_Type{ Type };
	if (Type != Last_Type)
	{
		Cur = 0;
		Last_Type = Type;
		Chain_Exac = 0x0000;
	}

	if (Exac != 0xFFFF)
		Chain_Exac = Exac;

	this->ResetInstance(true);
	this->Set_Internal_Id((Last_Type << 16) + Chain_Exac, "CHAIN_DATA_TYPE", "CHAIN_DATA_EXAC");
	Data_Link* DL{ new Data_Link(Cur, Data) };
	this->Set_Internal_Data(DL, SIMPLE_SET);
	this->AppendItem(APPENDTO_MEMO);
	Cur++;
	if (Cur == Div)
	{
		Cur = 0;
		Chain_Exac = (Chain_Exac == 0xFFFF ? 0x0000 : (Chain_Exac + 1));
	}
}

void TANXL_DataBase::Clear_DataChain()
{
	for (int i{ 0 }; i < this->_Id_Links->size(); ++i)
		std::vector<Data_Unit*>().swap(this->_Id_Links->at(i)->_Data->_Data_Units);
	std::vector<Id_Link*>().swap(*this->_Id_Links);
}

void TANXL_DataBase::Copy_DataBase(TANXL_DataBase& DataBase)
{
	this->_Id_Links->erase(this->_Id_Links->begin(), this->_Id_Links->end());
	for (const auto& Data : *DataBase._Id_Links)
		this->_Id_Links->push_back(Data);
}

const std::string TANXL_DataBase::Get_Version()
{
#if !_ENABLE_TANXL_DATABASE_INDEPENDENT_
	return Tanxl_ClassBase::Get_Version();
#else
	return "2.1";
#endif
}