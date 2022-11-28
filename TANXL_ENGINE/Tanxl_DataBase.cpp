#pragma once

#include "Tanxl_DataBase.h"

std::string Combine_Char(std::string data, int Start, int End)
{
	if (End < Start)
	{
		throw "错误 : Combine_Char 的输入值Start大于End的值";
		return "";
	}
	std::string New_data{};
	for (int i = Start, j = 0; i < End; i++, j++)
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
		throw "错误 : Divid_Char 没有此条目的功能(0~3 为合法内容，而你输入了" + std::to_string(Mode) + ")";
		return "";
	}
	for (int i = 0; i < data.length(); i++)//获取内容
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

void Reset_Chain(TANXL_DataBase TDB, int A, int B, int Nums)
{
	TDB.Set_Specified(A, B, Nums, 3, -1, "NULL");
	TDB.Set_Specified(A, B, Nums, 4, -1, "NULL");
	TDB.Set_Specified(A, B, Nums, 5, -1, "NULL");
}

void Data(bool Mode, bool Zero)
{
	TANXL_DataBase TDB_Instance(Zero);
	for (unsigned Content = 0x11111f55; Content < 0x11112111; Content++)
	{
		TDB_Instance.Set_Instance(0x10000000 | 0x0fffffff, "手枪");
		TDB_Instance.Set_Instance(Content & 0x0f000000 | 0xf0ffffff, "地下水");
		TDB_Instance.Set_Instance(Content & 0x00ff0000 | 0xff00ffff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x0000ff00 | 0xffff00ff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x000000ff | 0xffffff00, std::to_string(rand() % 100));
		if (Mode)std::cout << TDB_Instance;
		TDB_Instance.AppendItem();
	}
	for (unsigned Content = 0x22221f55; Content < 0x22222111; Content++)
	{
		TDB_Instance.Set_Instance(0x20000000 | 0x0fffffff, "步枪");
		TDB_Instance.Set_Instance(Content & 0x0f000000 | 0xf0ffffff, "M4A1-S");
		TDB_Instance.Set_Instance(Content & 0x00ff0000 | 0xff00ffff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x0000ff00 | 0xffff00ff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x000000ff | 0xffffff00, std::to_string(rand() % 100));
		if (Mode)std::cout << TDB_Instance;
		TDB_Instance.AppendItem();
	}
	for (unsigned Content = 0x33331f55; Content < 0x33332111; Content++)
	{
		TDB_Instance.Set_Instance(0x30000000 | 0x0fffffff, "重型武器");
		TDB_Instance.Set_Instance(Content & 0x0f000000 | 0xf0ffffff, "Nova");
		TDB_Instance.Set_Instance(Content & 0x00ff0000 | 0xff00ffff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x0000ff00 | 0xffff00ff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x000000ff | 0xffffff00, std::to_string(rand() % 100));
		if (Mode)std::cout << TDB_Instance;
		TDB_Instance.AppendItem();
	}
	for (unsigned Content = 0x44441f55; Content < 0x44442111; Content++)
	{
		TDB_Instance.Set_Instance(0x40000000 | 0x0fffffff, "微型冲锋枪");
		TDB_Instance.Set_Instance(Content & 0x0f000000 | 0xf0ffffff, "MP9");
		TDB_Instance.Set_Instance(Content & 0x00ff0000 | 0xff00ffff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x0000ff00 | 0xffff00ff, std::to_string(rand() % 100));
		TDB_Instance.Set_Instance(Content & 0x000000ff | 0xffffff00, std::to_string(rand() % 100));
		if (Mode)std::cout << TDB_Instance;
		TDB_Instance.AppendItem();
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

std::ostream& operator<<(std::ostream& fot, TANXL_DataBase& s)
{
	if ((s.Item_Instance.Status_1 + s.Item_Instance.Status_2 + s.Item_Instance.Status_3 + s.Item_Instance.Status_4 + s.Item_Instance.Status_5) || s.Is_Zero_Legal)
	{
		s.Get_Item_Status();
		fot << "<Type_Status : " << s.Item_Instance.Code << " / " << s.Item_Instance.Status_1 << ">" << std::endl;
		s.OstreamSpace(fot, 1); fot << "<Exac_Status : " << s.Item_Instance.Name << " / " << s.Item_Instance.Status_2 << ">" << std::endl;
		s.OstreamSpace(fot, 1, 1); fot << "<TDBS_Item>" << std::endl;
		if (s.Item_Instance.Status_3 || s.Is_Zero_Legal) {
			s.OstreamSpace(fot);
			fot << "<Oth1: " << s.Item_Instance.Status_3 << ">" << s.Item_Instance.Oth1 << "</Oth1>" << std::endl;
		}
		if (s.Item_Instance.Status_4 || s.Is_Zero_Legal) {
			s.OstreamSpace(fot);
			fot << "<Oth2: " << s.Item_Instance.Status_4 << ">" << s.Item_Instance.Oth2 << "</Oth2>" << std::endl;
		}
		if (s.Item_Instance.Status_5 || s.Is_Zero_Legal) {
			s.OstreamSpace(fot);
			fot << "<Oth3: " << s.Item_Instance.Status_5 << ">" << s.Item_Instance.Oth3 << "</Oth3>" << std::endl;
		}
		s.OstreamSpace(fot, -1); fot << "</TDBS_Item>" << std::endl;
		s.OstreamSpace(fot, -1); fot << "</Exac_Status>" << std::endl;
		s.OstreamSpace(fot, -1); fot << "</Type_Status>" << std::endl;
	}
	return fot;
}

inline void TANXL_DataBase::Set_Code(std::string set, unsigned status){ Item_Instance.Code = set; Item_Instance.Status_1 = status; Combine_Status(); }
inline void TANXL_DataBase::Set_Name(std::string set, unsigned status){ Item_Instance.Name = set; Item_Instance.Status_2 = status; Combine_Status(); }
inline void TANXL_DataBase::Set_Oth1(std::string set, unsigned status){ Item_Instance.Oth1 = set; Item_Instance.Status_3 = status; Combine_Status(); }
inline void TANXL_DataBase::Set_Oth2(std::string set, unsigned status){ Item_Instance.Oth2 = set; Item_Instance.Status_4 = status; Combine_Status(); }
inline void TANXL_DataBase::Set_Oth3(std::string set, unsigned status){ Item_Instance.Oth3 = set; Item_Instance.Status_5 = status; Combine_Status(); }

TANXL_DataBase::TANXL_DataBase(bool Zero_Legal) :
	Is_Instance_Data(false), Is_Chain_Empty(true), Is_Zero_Legal(Zero_Legal),
	IC_Vector(new std::vector<Id_Vector*>),Current_Location(0) {}

inline void TANXL_DataBase::OstreamSpace(std::ostream& os, int Before, int After)
{
	static int TDB_Status = 0;//级别数值 用于记录当前行的Tab数量
	TDB_Status += Before;
	for (int i = 0; i < TDB_Status; i++)os << "\t";
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
	Item_Instance.Status_1 = 0x0;
	Item_Instance.Status_2 = 0x0;
	Item_Instance.Status_3 = 0x00;
	Item_Instance.Status_4 = 0x00;
	Item_Instance.Status_5 = 0x00;
	Combine_Status();
	Is_Instance_Data = false;
}

void TANXL_DataBase::Set_Instance(unsigned Num, std::string Set)
{
	int SetTimes{ 0 };
	if (0 <= ((Num & 0xf0000000) >> 28) && ((Num & 0xf0000000) >> 28) < 15) {
		Set_Code(Set, ((Num & 0xf00000000) >> 28)); SetTimes++;
	}
	if (0 <= ((Num & 0x0f000000) >> 24) && ((Num & 0x0f000000) >> 24) < 15) {
		Set_Name(Set, ((Num & 0x0f000000) >> 24)); SetTimes++;
	}
	if (0 <= ((Num & 0x00ff0000) >> 16) && ((Num & 0x00ff0000) >> 16) < 255) {
		Set_Oth1(Set, ((Num & 0x00ff0000) >> 16)); SetTimes++;
	}
	if (0 <= ((Num & 0x0000ff00) >> 8) && ((Num & 0x0000ff00) >> 8) < 255) {
		Set_Oth2(Set, ((Num & 0x0000ff00) >> 8)); SetTimes++;
	}
	if (0 <= (Num & 0x000000ff) && (Num & 0x000000ff) < 255) {
		Set_Oth3(Set, (Num & 0x000000ff)); SetTimes++;
	}
	if (SetTimes)
		Is_Instance_Data = true;
}

void TANXL_DataBase::AppendItem(bool To_File, std::string File_Name)
{
	if (!Is_Instance_Data)
	{
		throw "添加失败！ 结构内容为空";
		return;
	}
	else if (To_File)
	{
		Is_Instance_Data = true;
		std::fstream out(File_Name, std::ios::app);
		if (out.is_open())
		{
			out << *this;
			this->ResetInstance();
			out.close();
		}
	}
	else
	{
		Data_Vector* DTemp = new Data_Vector(
			Item_Instance.Status_3, Item_Instance.Oth1,
			Item_Instance.Status_4, Item_Instance.Oth2,
			Item_Instance.Status_5, Item_Instance.Oth3);
		Id_Vector* ITemp = new Id_Vector(
			Item_Instance.Status_1, Item_Instance.Status_2,
			Item_Instance.Code, Item_Instance.Name);
		if (DTemp && ITemp)//判断是否申请空间成功
			Append_Chain(*DTemp, *ITemp);
		else
			throw "添加失败！ 申请内存空间失败";
	}
}

void TANXL_DataBase::SortDataBase(int Mode, std::string Out_File_Name, std::string In_File_Name)
{
	if (Mode == SORT_LOCALF)
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
	Id_Vector* PIC{ this->IC_Vector->at(0)};
	out << "<Tanxl_DataBase Information>" << std::endl;
	std::vector<Id_Vector*>::iterator IOIE{ IC_Vector->end()};
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
			if ((*IODB)->Id_1 + (*IODB)->Id_2 + (*IODB)->Id_3 == -3)
				continue;
			out << "\t\t\t<TDB_Item>" << std::endl;
			if ((*IODB)->Id_1 || Is_Zero_Legal)
				out << "\t\t\t\t<Oth1: " << (*IODB)->Id_1 << ">" << (*IODB)->Sd_1 << "</Oth1>" << std::endl;
			if ((*IODB)->Id_2 || Is_Zero_Legal)
				out << "\t\t\t\t<Oth2: " << (*IODB)->Id_2 << ">" << (*IODB)->Sd_2 << "</Oth2>" << std::endl;
			if ((*IODB)->Id_3 || Is_Zero_Legal)
				out << "\t\t\t\t<Oth3: " << (*IODB)->Id_3 << ">" << (*IODB)->Sd_3 << "</Oth3>" << std::endl;
			out << "\t\t\t</TDB_Item>" << std::endl;
			IODB++;
		} while (IODB != IODE);
		out << "\t\t</Exac_Status>" << std::endl;
		out << "\t</Type_Status>" << std::endl;
		IOIB++;
	} while (IOIB != IOIE);
	out << "</Tanxl_DataBase Information>" << std::endl;
	out.close();
	Clear_Chain();
	if (Mode == SORT_LOCALF)
	{
		std::string s = In_File_Name + ".usd";
		remove(s.c_str());
	}
}

void TANXL_DataBase::Append_Chain(Data_Vector& New_Data, Id_Vector& New_Id)
{
	if (Is_Chain_Empty)
	{
		IC_Vector->push_back(&New_Id);
		IC_Vector->at(0)->exac->push_back(&New_Data);
		Is_Chain_Empty = false;
		return;
	}
	int Left{ 0 }, Value{ New_Id.Type * 16 + New_Id.Exac },
		Right{ static_cast<int>(IC_Vector->size()) - 1 <= 0 ? 0 : static_cast<int>(IC_Vector->size()) - 1 };
	while (true)
	{
		int Mid{ (Left + Right) / 2 };
		Id_Vector* PIC = IC_Vector->at(Mid);
		int PIC_Value{ PIC->Type * 16 + PIC->Exac };
		if (PIC_Value == Value)//Type B匹配时
		{
			PIC->exac->push_back(&New_Data);
			Is_Chain_Empty = false;
			return;
		}
		else if (Left == Right && PIC_Value != Value)//Type B不匹配 但已经是最接近的值时
		{
			if (PIC_Value < Value)
				Left += 1;
			this->IC_Vector->insert(IC_Vector->begin() + Left, &New_Id);
			IC_Vector->at(Left)->exac->push_back(&New_Data);
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
	throw "Append() Failed ! : 未知原因";
	return;
}

bool TANXL_DataBase::Get_LocalData(std::string File_Name)
{
	std::fstream in(File_Name + ".usd", std::ios::in);
	if (!in.is_open())
		std::fstream in(File_Name + ".sd", std::ios::in);
	if (in.is_open())
	{
		std::string Type_Data{}, Exac_Data{};//需要使用时再定义
		int  Type_Stat{}, Exac_Stat{};
		int IData[3]{ 0 }, Target{ -1 };
		std::string SData[3]{};
		std::string Line{};
		while (std::getline(in, Line))
		{
			std::string Tag{ Combine_Char(Line, 1, 5) };
			if (Tag == "Type")
			{
				Type_Stat = std::stoi(Divid_Char(Line, GET_STATUS_DAT));
				Type_Data = Divid_Char(Line, GET_STATUS_STR);
				std::getline(in, Line);
				Exac_Stat = std::stoi(Divid_Char(Line, GET_STATUS_DAT));
				Exac_Data = Divid_Char(Line, GET_STATUS_STR);
				while (std::getline(in, Line))
				{
					Tag = Combine_Char(Line, 1, 5);
					if (Tag == "Type")
					{
						Type_Stat = std::stoi(Divid_Char(Line, GET_STATUS_DAT));
						Type_Data = Divid_Char(Line, GET_STATUS_STR);
					}
					else if (Tag == "Exac")
					{
						Exac_Stat = std::stoi(Divid_Char(Line, GET_STATUS_DAT));
						Exac_Data = Divid_Char(Line, GET_STATUS_STR);
					}
					else if (Tag == "/TDB")
					{
						Data_Vector* Data_Temp = new Data_Vector(IData[0], SData[0], IData[1], SData[1], IData[2], SData[2]);
						Id_Vector* Id_Temp = new Id_Vector(Type_Stat, Exac_Stat, Type_Data, Exac_Data);
						IData[0] = 0; IData[1] = 0; IData[2] = 0; SData[0] = ""; SData[1] = ""; SData[2] = "";
						if (Data_Temp && Id_Temp)
							Append_Chain(*Data_Temp, *Id_Temp);
						else
							throw "添加失败！ 申请内存空间失败";
						continue;
					}
					else if (Tag == "Oth1")
						Target = 0;
					else if (Tag == "Oth2")
						Target = 1;
					else if (Tag == "Oth3")
						Target = 2;
					if (Target == -1)
						continue;
					IData[Target] = std::stoi(Divid_Char(Line, GET_OLDSTY_DAT));
					SData[Target] = Divid_Char(Line, GET_STORAG_DAT);
					Target = -1;
				}
			}
		}
		in.close();
		return true;
	}
	else
		return false;
}

void TANXL_DataBase::Clear_Chain()
{
	for (int i = 0; i < IC_Vector->size(); i++)
		Remove_Chain(IC_Vector->at(i)->Type, IC_Vector->at(i)->Exac);
	Is_Chain_Empty = true;
}

void TANXL_DataBase::Get_Specified(int Type, int Exac, int Nums)
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
}

void TANXL_DataBase::Get_Item_Status()
{
	Item_Instance.Status_1 = ((Item_Instance.Item_Status & 0xf0000) >> 16);
	Item_Instance.Status_2 = ((Item_Instance.Item_Status & 0x0f000) >> 12);
	Item_Instance.Status_3 = ((Item_Instance.Item_Status & 0x00f00) >> 8 );
	Item_Instance.Status_4 = ((Item_Instance.Item_Status & 0x000f0) >> 4 );
	Item_Instance.Status_5 = ( Item_Instance.Item_Status & 0x0000f       );
}

void TANXL_DataBase::Print_Data()//输出当前链表中的所有内容 V3 Updated
{
	if (!Is_Chain_Empty)
	{
		Id_Vector* PIC{};
		Data_Vector* PDC{};
		int PIC_Count{ 0 };
		std::vector<Id_Vector*>::iterator IOI = IC_Vector->end() - 1;
		do
		{
			int PDC_Count{ 0 };
			PIC = this->IC_Vector->at(PIC_Count++);
			std::vector<Data_Vector*>::iterator IOD = PIC->exac->end() - 1;
			std::cout << "Id_Vector :" << PIC->Type << " - " << PIC->StrA << " - " << PIC->Exac << " - " << PIC->StrB << std::endl;
			do
			{
				PDC = PIC->exac->at(PDC_Count++);
				std::cout << "\tData_Vector :" << PDC->Id_1 << "-" << PDC->Id_2 << "-" << PDC->Id_3 << std::endl;
			} while (PDC != *IOD);
		} while (PIC != *IOI);
		return;
	}
	throw "Print_Data() Failed ！ : 链表内容为空";
}

void TANXL_DataBase::Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data) //V3 Updated
{
	if (Data_Vector * PDC{ Data_Chain_Locate(Type, Exac, Nums) })
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
}

void TANXL_DataBase::Remove_Chain(int Type, int Exac)
{
	if (Id_Vector * PIC{ Id_Chain_Locate(Type, Exac) })
	{
		for (int i{ 0 }; i < PIC->exac->size(); i++)
			delete PIC->exac->at(i);//释放 Data_Vector
		PIC->exac->clear();
		delete PIC;//释放 Id_Vector
		IC_Vector->erase(IC_Vector->begin() + Current_Location);
	}
}

Id_Vector* TANXL_DataBase::Id_Chain_Locate(int Type, int Exac)
{
	int Left{ 0 },Value{ Type * 16 + Exac },
		Right{ static_cast<int>(IC_Vector->size()) - 1 >= 0 ? static_cast<int>(IC_Vector->size()) - 1 : 0 };;
	if (Left == Right)
	{
		if (Value == IC_Vector->at(0)->Type * 16 + IC_Vector->at(0)->Exac)
		{
			Current_Location = 0;
			return IC_Vector->at(0);
		}
		throw "Id_Chain_Locate Failed ! : 未能成功匹配相同值";
		return NULL;
	}
	else
	{
		while (Left != Right)
		{
			int Mid{ (Left + Right) / 2 };
			int Mid_Value{ IC_Vector->at(Mid)->Type * 16 + IC_Vector->at(Mid)->Exac };
			if (Mid_Value == Value)
			{
				Current_Location = Mid;
				return IC_Vector->at(Mid);
			}
			else if (Mid_Value > Value)
				Right = Mid;
			else if (Mid_Value < Value)
				Left = Mid;
			if (Left == Right)
			{
				throw "Id_Chain_Locate Failed ! : 未能成功匹配相同值";
				return NULL;
			}
		}
	}
	throw "Id_Chain_Locate Failed ! : 未知原因";
	return NULL;
}

Data_Vector* TANXL_DataBase::Data_Chain_Locate(int Type, int Exac, int Depth)
{
	Id_Vector* PIC{ Id_Chain_Locate(Type, Exac) };
	if (PIC->exac->size() < Depth)
	{
		throw "Data_Chain_Locate Failed ! : 超出当前容器最大深度";
		return NULL;
	}
	else if (Depth < 0 && Depth + static_cast<int>(PIC->exac->size()) >= 0)
		return PIC->exac->at(Depth + PIC->exac->size());
	while (Depth + static_cast<int>(PIC->exac->size() < 0))
		Depth += static_cast<int>(PIC->exac->size());
	return PIC->exac->at(Depth);
}

void TANXL_DataBase::Replace_Chain(int OldType, int OldExac, int OldDepth, int Type, int Exac)
{
	Id_Vector* PIC{ Id_Chain_Locate(OldType, OldExac) };
	Append_Chain(*PIC->exac->at(OldDepth), *new Id_Vector(Type, Exac));
	if (PIC->exac->size() > OldDepth && OldDepth >= 0)
		PIC->exac->erase(PIC->exac->begin() + OldDepth);
	else if (PIC->exac->size() + OldDepth >= 0 && PIC->exac->size() + OldDepth < PIC->exac->size())
		PIC->exac->erase(PIC->exac->begin() + PIC->exac->size() + OldDepth);
}