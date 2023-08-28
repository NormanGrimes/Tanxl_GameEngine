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

std::ostream& operator<<(std::ostream& out, TANXL_DataBase& s)
{
	out << "<Type_Status : " << s._Internal_Data._Type_Name << " / " << ((s._Internal_Data._Item_Status & 0xFF00) >> 8) << ">" << std::endl;
	s.OstreamSpace(out, 1); out << "<Exac_Status : " << s._Internal_Data._Exac_Name << " / " << (s._Internal_Data._Item_Status & 0x00FF) << ">" << std::endl;
	s.OstreamSpace(out, 1, 1); out << "<TDBS_Item>" << std::endl;
	for (int i = 0; i < s._Internal_Data._Data->_Data_Units.size(); ++i)
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
	Is_Instance_Data(false), _Id_Links(new std::vector<Id_Link*>),Current_Location(0) {}

inline void TANXL_DataBase::OstreamSpace(std::ostream& os, int Before, int After)
{
	static int TDB_Status = 0;//级别数值 用于记录当前行的Tab数量
	TDB_Status += Before;
	for (int i = 0; i < TDB_Status; ++i)os << "\t";
	TDB_Status += After;
}

void TANXL_DataBase::ResetInstance(bool Delete)
{
	this->_Internal_Data._Item_Status = 0xFFFF;
	this->_Internal_Data._Type_Name = "";
	this->_Internal_Data._Exac_Name = "";
	if (Delete && this->_Internal_Data._Data != nullptr)
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
		Id_Link* IdLink = new Id_Link(
			(this->_Internal_Data._Item_Status & 0xff00) >> 8, this->_Internal_Data._Type_Name,
			this->_Internal_Data._Item_Status & 0x00ff, this->_Internal_Data._Exac_Name,
			new Data_Link(this->_Internal_Data._Data)
		);
		if (IdLink)//判断是否申请空间成功//UNFINISH YET
			Append_Link(*IdLink);
		else
			throw "添加失败！ 申请内存空间失败";
	}
	this->ResetInstance(Delete_After);
}

void TANXL_DataBase::SortDataBase(int Mode, std::string Out_File_Name, std::string In_File_Name, bool Delete_After_Sort)
{
	if (Mode == SORT_LOCALF || Mode == FILE_UNITED)
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
	do
	{
		std::cout << "(*IOIB)" << (*IOIB)->_Data->_Data_Units.size() << std::endl;
		std::vector<Data_Unit*>::iterator IODE{ (*IOIB)->_Data->_Data_Units.end()};
		std::vector<Data_Unit*>::iterator IODB{ (*IOIB)->_Data->_Data_Units.begin() };
		std::cout << "\t<Type_Status : " << (*IOIB)->_Type_Name << " / " << (*IOIB)->_Type << ">" << std::endl;
		std::cout << "\t\t<Exac_Status : " << (*IOIB)->_Exac_Name << " / " << (*IOIB)->_Exac << ">" << std::endl;
		out << "\t<Type_Status : " << (*IOIB)->_Type_Name << " / " << (*IOIB)->_Type << ">" << std::endl;
		out << "\t\t<Exac_Status : " << (*IOIB)->_Exac_Name << " / " << (*IOIB)->_Exac << ">" << std::endl;

		do
		{
			std::string TAG = DataTag((*IOIB)->_Type, (*IOIB)->_Exac, (*IODB)->_Id);
			TAG = (TAG == "" ? "DATA" : TAG);
			out << "\t\t\t<" + TAG + ": " << (*IODB)->_Id << ">" << (*IODB)->_Data << "</" + TAG + ">" << std::endl;
			std::cout << "\t\t\t<" + TAG + ": " << (*IODB)->_Id << ">" << (*IODB)->_Data << "</" + TAG + ">" << std::endl;
			++IODB;
		} while (IODB != IODE);
		out << "\t\t</Exac_Status>" << std::endl;
		out << "\t</Type_Status>" << std::endl;
		++IOIB;
	} while (IOIB != IOIE);
	out << "</Tanxl_DataBase Information>" << std::endl;
	out.close();
	if (Delete_After_Sort)
	{
		if (Mode == SORT_LOCALF || Mode == FILE_UNITED)
		{
			std::string s = In_File_Name + ".usd";
			remove(s.c_str());
		}
	}
}

void TANXL_DataBase::Append_Link(Id_Link& New_Id)
{
	if (this->_Id_Links->size() == 0)
	{
		this->_Id_Links->insert(this->_Id_Links->begin(), &New_Id);
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
			PIC->_Data->Append_Data(New_Id._Data);
			return;
		}
		else if (Left == Right && PIC_Value != Value)//Type B不匹配 但已经是最接近的值时
		{
			if (PIC_Value < Value)
				Left += 1;
			this->_Id_Links->insert(this->_Id_Links->begin() + Left, &New_Id);
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
	for (int i = 0; i < this->_Id_Links->size(); ++i)
	{
		delete this->_Id_Links->at(i)->_Data;
		delete this->_Id_Links->at(i);
	}
	delete this->_Id_Links;
	this->_Id_Links = new std::vector<Id_Link*>;
	std::fstream in(File_Name + ".usd", std::ios::in);
	if (!in.is_open())
		std::fstream in(File_Name + ".sd", std::ios::in);
	if (in.is_open())
	{
		std::string Type_Data{}, Exac_Data{}, Data{};//需要使用时再定义
		int  Type_Stat{}, Exac_Stat{}, Id{};
		Data_Link DTL;
		std::string Line{};
		while (std::getline(in, Line))
		{
			std::cout << Line << std::endl;
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
			}
			else if (Tag == "/TDB")
			{
				Id_Link* Id_Temp = new Id_Link(Type_Stat, Type_Data, Exac_Stat, Exac_Data, &DTL);
				std::vector<Data_Unit*>().swap(DTL._Data_Units);//释放内存
				if (Id_Temp)
				{
					Append_Link(*Id_Temp);
					std::cout << "1";
				}
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
				DTL.Append_Data(Id, Data);
			}
		}
		in.close();
		return true;
	}
	else
		return false;
}

void TANXL_DataBase::Get_Specified(int Type, int Exac, int Depth)
{
	if (Data_Unit * PDC{ Data_Link_Locate(Type, Exac, Depth) })
	{
		Id_Link* PIC = { Id_Link_Locate(Type, Exac) };
		this->_Internal_Data._Item_Status = ((PIC->_Type << 8) + PIC->_Exac);
		this->_Internal_Data._Type_Name = PIC->_Type_Name;
		this->_Internal_Data._Exac_Name = PIC->_Exac_Name;
		this->_Internal_Data._Data = PIC->_Data;
		return;
	}
	throw "Get_Specified() Failed ！ : 未能成功匹配相同值";
}

void TANXL_DataBase::Print_Data()
{
	std::vector<Id_Link*>::iterator BOI{ this->_Id_Links->begin() };
	std::vector<Id_Link*>::iterator EOI{ this->_Id_Links->end() };
	while (BOI != EOI)
	{
		std::cout << "Id_Link :" << (*BOI)->_Type << " - " << (*BOI)->_Type_Name << " - " << (*BOI)->_Exac << " - " << (*BOI)->_Exac_Name << std::endl;
		Data_Link* DL{ ((*BOI)->_Data) };
		if (DL == nullptr)
			break;
		for (int i = 0; i < DL->_Data_Units.size(); ++i)
			std::cout << "\tData_Link :" << DL->_Data_Units.at(i)->_Id << " - " << DL->_Data_Units.at(i)->_Data << std::endl;
		++BOI;
	}
}

void TANXL_DataBase::Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data) //V3 Updated
{
	if (Data_Unit * PDC{Data_Link_Locate(Type, Exac, Nums)})
		switch (level)
		{
		case SET_TYPE_STATUS:
			Replace_Link(Type, Exac, Nums, Id, Data);
			return;
		case SET_EXAC_STATUS:
			Replace_Link(Type, Exac, Nums, Type, Data);
			return;
		case SET_UNIT_IDADAT:
			PDC->_Id = Id;
			PDC->_Data = Data;
			return;
		}
	throw "Set_Specified() Failed ！ : 查找相关内容不成功或链表内容为空";
}

void TANXL_DataBase::Remove_Link(int Type, int Exac)
{
	if (Id_Link * PIC{Id_Link_Locate(Type, Exac)})
	{
		std::vector<Data_Unit*>().swap(PIC->_Data->_Data_Units);
		delete PIC;
		_Id_Links->erase(_Id_Links->begin() + Current_Location);
	}
}

Id_Link* TANXL_DataBase::Id_Link_Locate(int Type, int Exac)
{
	int Left{ 0 }, Value{ Type * 16 + Exac },
		Right{ static_cast<int>(this->_Id_Links->size()) - 1 >= 0 ? static_cast<int>(this->_Id_Links->size()) - 1 : 0 };
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
		return PIC->_Data->_Data_Units.at(Depth + PIC->_Data->_Data_Units.size());
	while (Depth + static_cast<int>(PIC->_Data->_Data_Units.size() < 0))
		Depth += static_cast<int>(PIC->_Data->_Data_Units.size());
	return PIC->_Data->_Data_Units.at(Depth);
}

void TANXL_DataBase::Replace_Link(int OldType, int OldExac, int OldDepth, int Id, std::string Data)
{
	Id_Link* PIC{ Id_Link_Locate(OldType, OldExac) };
	PIC->_Data->Append_Data(Id, Data);
	if (PIC->_Data->_Data_Units.size() > OldDepth && OldDepth >= 0)
		PIC->_Data->_Data_Units.erase(PIC->_Data->_Data_Units.begin() + OldDepth);
	else if (PIC->_Data->_Data_Units.size() + OldDepth >= 0 && PIC->_Data->_Data_Units.size() + OldDepth < PIC->_Data->_Data_Units.size())
		PIC->_Data->_Data_Units.erase(PIC->_Data->_Data_Units.begin() + PIC->_Data->_Data_Units.size() + OldDepth);
}

void TANXL_DataBase::Append_DataChain(std::string Data, unsigned Divide)
{
	static int Div = static_cast<int>(Divide);
	static int Cur = 0;
	if (Divide != 0)
		Div = Divide;
	static unsigned Type = 0x01;
	static unsigned Exac = 0x00;
	this->ResetInstance(true);
	this->Set_Internal_Id((Type << 8) + Exac, "CHAIN_DATA_TYPE", "CHAIN_DATA_EXAC");
	Data_Link* DL = new Data_Link(Cur, Data);
	this->Set_Internal_Data(DL, SIMPLE_SET);
	this->AppendItem(APPENDTO_FILE, "Data_Chain_File", true);
	Cur++;
	if (Cur == Div)
	{
		Cur = 0;
		Exac = (Exac + 1) > 0xFF ? 0x00 : (Exac + 1);
	}
}

const std::string TANXL_DataBase::Get_Version()
{
	return this->_Version;
}