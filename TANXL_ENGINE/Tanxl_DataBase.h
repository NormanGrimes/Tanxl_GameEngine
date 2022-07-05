//_VERSION_1_5_ UPDATE LOG
// LAST_UPDATE 2022-04-04 23:42:47
// �����쳣������
// Combine_File()���ڿ��������
// ����new�����Ƿ�ɹ����ж�

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

enum ESet_Instance
{
	SET_TYPE_0  = 0x00000, SET_EXAC_0  = 0x00000, SET_OTH1_0  = 0x00000, SET_OTH2_0  = 0x00000, SET_OTH3_0  = 0x00000,
	SET_TYPE_1  = 0x10000, SET_EXAC_1  = 0x01000, SET_OTH1_1  = 0x00100, SET_OTH2_1  = 0x00010, SET_OTH3_1  = 0x00001,
	SET_TYPE_2  = 0x20000, SET_EXAC_2  = 0x02000, SET_OTH1_2  = 0x00200, SET_OTH2_2  = 0x00020, SET_OTH3_2  = 0x00002,
	SET_TYPE_3  = 0x30000, SET_EXAC_3  = 0x03000, SET_OTH1_3  = 0x00300, SET_OTH2_3  = 0x00030, SET_OTH3_3  = 0x00003,
	SET_TYPE_4  = 0x40000, SET_EXAC_4  = 0x04000, SET_OTH1_4  = 0x00400, SET_OTH2_4  = 0x00040, SET_OTH3_4  = 0x00004,
	SET_TYPE_5  = 0x50000, SET_EXAC_5  = 0x05000, SET_OTH1_5  = 0x00500, SET_OTH2_5  = 0x00050, SET_OTH3_5  = 0x00005,
	SET_TYPE_6  = 0x60000, SET_EXAC_6  = 0x06000, SET_OTH1_6  = 0x00600, SET_OTH2_6  = 0x00060, SET_OTH3_6  = 0x00006,
	SET_TYPE_7  = 0x70000, SET_EXAC_7  = 0x07000, SET_OTH1_7  = 0x00700, SET_OTH2_7  = 0x00070, SET_OTH3_7  = 0x00007,
	SET_TYPE_8  = 0x80000, SET_EXAC_8  = 0x08000, SET_OTH1_8  = 0x00800, SET_OTH2_8  = 0x00080, SET_OTH3_8  = 0x00008,
	SET_TYPE_9  = 0x90000, SET_EXAC_9  = 0x09000, SET_OTH1_9  = 0x00900, SET_OTH2_9  = 0x00090, SET_OTH3_9  = 0x00009,
	SET_TYPE_10 = 0xa0000, SET_EXAC_10 = 0x0a000, SET_OTH1_10 = 0x00a00, SET_OTH2_10 = 0x000a0, SET_OTH3_10 = 0x0000a,
	SET_TYPE_11 = 0xb0000, SET_EXAC_11 = 0x0b000, SET_OTH1_11 = 0x00b00, SET_OTH2_11 = 0x000b0, SET_OTH3_11 = 0x0000b,
	SET_TYPE_12 = 0xc0000, SET_EXAC_12 = 0x0c000, SET_OTH1_12 = 0x00c00, SET_OTH2_12 = 0x000c0, SET_OTH3_12 = 0x0000c,
	SET_TYPE_13 = 0xd0000, SET_EXAC_13 = 0x0d000, SET_OTH1_13 = 0x00d00, SET_OTH2_13 = 0x000d0, SET_OTH3_13 = 0x0000d,
	SET_TYPE_14 = 0xe0000, SET_EXAC_14 = 0x0e000, SET_OTH1_14 = 0x00e00, SET_OTH2_14 = 0x000e0, SET_OTH3_14 = 0x0000e,
	SET_TYPE_15 = 0xf0000, SET_EXAC_15 = 0x0f000, SET_OTH1_15 = 0x00f00, SET_OTH2_15 = 0x000f0, SET_OTH3_15 = 0x0000f,
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
		Type(Type), Exac(Exac), StrA(Code), StrB(Name), exac(NULL) {}
	int Type, Exac;
	std::string StrA, StrB;
	std::vector<Data_Vector*> exac;//����֧���۰����
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

	std::vector<Id_Vector*> IC_Vector;
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
	//���༭ʵ�� 0x12345 1����Codeλ 2����Nameλ 3����Oth1λ ��������  ����Is_Zero_LegalΪfalseʱ������������
	//����Ϸ�ʱ���ܵ�ʮ��������Ϊ6λ 0x123456 6���ڱ�ʾ��ǰָ���λ��� ��Χ1~5 1���� Oth3λ 2���� Oth2λ... �����һλ���� ����λ���㲻�Ϸ�ʱ��ȫ�෴
	void Set_Instance(unsigned Num, std::string Set);
	void Get_Specified(int Type, int Exac, int Nums);//��ȡָ��Type(A)_Exac(B)�������Ʒ �����뵽�����ṹ�� Nums��ʾ�����еĵڼ���(��0��ʼ)
	//���޸�ָ��Type(A)_Exac(B)�������Ʒ Nums��ʾ�����еĵڼ���(��0��ʼ) levelȡֵ��ΧΪ1~5 ����ѡ��Type Exac Oth1 ...
	//���޸�OTH1 OTH2 OTH3��ʱ��ֱ�Ӹ���������� �޸�TYPE-EXACʱ ��ת�Ƶ�ǰData_Chain���µķ����޸ĺ��TYPE-EXAC��Id_Chain��
	void Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data);
	void Remove_Chain(int Type, int Exac);//ɾ��ĳһ�ڵ���������������
	//�������ǰ�ڴ��е�������������� ��֧�����Id_Vector��Data_Vector�е�����
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