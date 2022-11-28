//_VERSION_1_7_ UPDATE LOG
// LAST_UPDATE 2022-08-26 20:20
// ʹ�ð�λʮ������ֵ��Ϊ��Ʒ���
// ͳһ��Ϸ��벻�Ϸ��������Ʒ����
// Ĭ�����ݺ����޸���֧��������ӷ�ʽ
// �Ƴ�Դ�ļ��ж����ȫ��TDB����

#pragma once

#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif

#ifndef FSTREAM
#define FSTREAM
#include<fstream>
#endif

#ifndef STRING
#define STRING
#include<string>
#endif

#ifndef SSTREAM
#define SSTREAM
#include<sstream>
#endif

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

enum ESort_Mode//ΪSortDataBase�����ṩ�Ĺ���ö��
{
	SORT_LOCALF = 0,
	SORT_MEMORY = 2,
};

enum EDivid_Mode//ΪDivid_Char�����ṩ�Ĺ���ö��
{
	GET_STATUS_DAT = 0,
	GET_STORAG_DAT = 1,
	GET_STATUS_TAG = 2,
	GET_STATUS_STR = 3,
	GET_OLDSTY_DAT = 4
};

enum ESet_Specified
{
	SET_TYPE_STATUS = 0,
	SET_EXAC_STATUS = 1,
	SET_OTH1_STATUS = 2,
	SET_OTH2_STATUS = 3,
	SET_OTH3_STATUS = 4,
};

struct Data_Vector//�����ݱ�(Vector)
{
	explicit Data_Vector(int I_A = 0, std::string D_A = NULL, int I_B = 0, std::string D_B = NULL, int I_C = 0, std::string D_C = NULL) :
		Id_1(I_A), Id_2(I_B), Id_3(I_C), Sd_1(D_A), Sd_2(D_B), Sd_3(D_C) {}
	int Id_1, Id_2, Id_3;
	std::string Sd_1, Sd_2, Sd_3;
};

struct Id_Vector//�����ͱ�(Vector)
{
	explicit Id_Vector(int Type, int Exac, std::string Code = "NULL", std::string Name = "NULL") :
		Type(Type), Exac(Exac), StrA(Code), StrB(Name), exac(new std::vector<Data_Vector*>) {}
	int Type, Exac;
	std::string StrA, StrB;
	std::vector<Data_Vector*>* exac;//����֧���۰����
};

class TANXL_DataBase
{
private:
	struct
	{
		unsigned Item_Status{ 0 };
		unsigned Status_1{}; std::string Code;
		unsigned Status_2{}; std::string Name;
		unsigned Status_3{}; std::string Oth1;
		unsigned Status_4{}; std::string Oth2;
		unsigned Status_5{}; std::string Oth3;
	}Item_Instance;

	std::vector<Id_Vector*>* IC_Vector;
	int Current_Location;
	bool Is_Instance_Data;//�����ж�Item_Instance���Ƿ�������
	bool Is_Chain_Empty;//�����ж������Ƿ�Ϊ��
	bool Is_Zero_Legal;//ֵΪtrueʱ0��Ϊ�Ϸ�ֵ �����������ʾ/ʹ��
	inline void Set_Code(std::string set, unsigned status);
	inline void Set_Name(std::string set, unsigned status);
	inline void Set_Oth1(std::string set, unsigned status);
	inline void Set_Oth2(std::string set, unsigned status);
	inline void Set_Oth3(std::string set, unsigned status);
	Id_Vector* Id_Chain_Locate(int Type, int Exac);//ʱ�临�Ӷ�ΪlogN��Id_Chain���ٶ�λ���� Type Exac ָId_Chain��ͬ������
	Data_Vector* Data_Chain_Locate(int Type, int Exac, int Depth);//����Id_Chain_Locate�����Բ�ͬ��ȵ�Data_Chain��λ
	void Replace_Chain(int OldType, int OldExac, int OldDepth, int Type, int Exac);//ת��Data_Chain����һ��Id_Chain��
	void Append_Chain(Data_Vector& New_Data, Id_Vector& New_Id);//�����������V3 ��ӵ�Vector��
	void Get_Item_Status();//��ȡ��Ʒ��ֵ �����ص��ṹ��
	void Clear_Chain();//��������
	void ResetInstance();//����Item�ṹ������
	inline void OstreamSpace(std::ostream& os, int Before = 0, int After = 0);//���ݼ�������ո� Before����ִ��ǰ�Լ�����ֵ�����޸� After����ִ�к�
	inline void Combine_Status();//���Status����Ʒ���𲢺ϲ���Item_Instance��
public:
	TANXL_DataBase(bool Zero_Legal = false);//���캯��
	bool Get_LocalData(std::string File_Name);//��ȡ�������� ���½�һ������ ֧�ִ������ʽ���ļ�(.usd .sd)
	//���༭ʵ�� 0x12030405 1����Codeλ 2����Nameλ 03����Oth1λ ��������
	//����1.7�汾�п��ǵ���Ϸ��Ĳ���һ���� ���ֵ�ѱ���Ϊ����ѡ��־�� Code/Nameλ��F ��Othλ��FF
	void Set_Instance(unsigned Num, std::string Set);
	void Get_Specified(int Type, int Exac, int Nums);//��ȡָ��Type(A)_Exac(B)�������Ʒ �����뵽�����ṹ�� Nums��ʾ�����еĵڼ���(��0��ʼ)
	//���޸�ָ��Type(A)_Exac(B)�������Ʒ Nums��ʾ�����еĵڼ���(��0��ʼ) levelȡֵ��ΧΪ1~5 ����ѡ��Type Exac Oth1 ...
	//���޸�OTH1 OTH2 OTH3��ʱ��ֱ�Ӹ���������� �޸�TYPE-EXACʱ ��ת�Ƶ�ǰData_Chain���µķ����޸ĺ��TYPE-EXAC��Id_Chain��
	void Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data);
	void Remove_Chain(int Type, int Exac);//ɾ��ĳһ�ڵ���������������
	//�������ǰ�ڴ��е�������������� ��֧�����Id_Vector��Data_Vector�е����� ��ǰ�ڴ�Ϊ��ʱ���׳�����
	void Print_Data();
	void AppendItem(bool To_File = true, std::string File_Name = "Tanxl_DataBase.usd");//�򱾵��ļ���(.usd)���Item��Ʒ �˺����ᵼ��Item��������
	//��ʹ����(.usd)�ļ������ݺ��� In_File_NameΪ�����ļ��� Out_File_NameΪ����ļ��� ���ھ��б��������޸Ĺ���
	//��ModeΪtrueʱ���ļ��ж�ȡ���� ��Ҫ�ṩIn/Out_File_Name ִ�к�����ڴ��е�����  ModeΪfalseʱֱ�ӶԵ�ǰ�ڴ��е������������ ����ʹ���������Ϊ���� ִ�к����
	void SortDataBase(int Mode = SORT_LOCALF, std::string Out_File_Name = "Tanxl_Data", std::string In_File_Name = "Tanxl_DataBase");
	friend std::ostream& operator<<(std::ostream& fot, TANXL_DataBase& s);//����ֱ�������ǰItem�����ڵ���Ϣ
};

std::string Combine_Char(std::string data, int Start, int End);//���char�����ȡָ�����ݣ�StartΪ��ʼλ��EndΪ����λ��(����λ�ò�����)

std::string Divid_Char(std::string data, int Mode = GET_STATUS_DAT);//��ֵ������ݻ�ȡ��Ϣ

void Reset_Chain(TANXL_DataBase TDB, int Type, int Exac, int Nums);//��������ĳһ��Ԫ Nums��ʾA,B level�µĵڼ���(��0��ʼ)

void Data(bool Mode = true, bool Zero = true);//������Ĭ������ Ϊtrueʱÿ����ӵ�ͬʱ��������Ļ�ϴ�ӡ Zero����ѡ�����ģʽ ΪTrueʱ��ӵ�Ϊ0�Ϸ�������

void Combine_File(std::string FileA, std::string FileB);//��FileA��FileB���������ϵ�FileA�� ����USD��ʽ�ļ�ʹ��