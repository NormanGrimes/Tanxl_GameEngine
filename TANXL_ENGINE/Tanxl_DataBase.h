//_VERSION_1_5_ UPDATE LOG
// LAST_UPDATE 2022-04-04 23:42:47
// 加入异常处理功能
// Combine_File()现在可任意组合
// 加入new申请是否成功的判断

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

enum ESort_Mode//为SortDataBase函数提供的功能枚举
{
	SORT_LOCALF = 0,
	SORT_MEMORY = 2,
};

enum EDivid_Mode//为Divid_Char函数提供的功能枚举
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

struct Data_Vector//短数据表(Vector)
{
	explicit Data_Vector(int I_A = 0, std::string D_A = NULL, int I_B = 0, std::string D_B = NULL, int I_C = 0, std::string D_C = NULL) :
		Id_1(I_A), Id_2(I_B), Id_3(I_C), Sd_1(D_A), Sd_2(D_B), Sd_3(D_C) {}
	int Id_1, Id_2, Id_3;
	std::string Sd_1, Sd_2, Sd_3;
};

struct Id_Vector//短类型表(Vector)
{
	explicit Id_Vector(int Type, int Exac, std::string Code = "NULL", std::string Name = "NULL") :
		Type(Type), Exac(Exac), StrA(Code), StrB(Name), exac(NULL) {}
	int Type, Exac;
	std::string StrA, StrB;
	std::vector<Data_Vector*> exac;//用于支持折半查找
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
	bool Is_Instance_Data;//用来判断Item_Instance中是否有数据
	bool Is_Chain_Empty;//用来判断链表是否为空
	bool Is_Zero_Legal;//值为true时0成为合法值 可在输出中显示/使用
	inline void Set_Code(std::string set, unsigned status);
	inline void Set_Name(std::string set, unsigned status);
	inline void Set_Oth1(std::string set, unsigned status);
	inline void Set_Oth2(std::string set, unsigned status);
	inline void Set_Oth3(std::string set, unsigned status);
	Id_Vector* Id_Chain_Locate(int Type, int Exac);//时间复杂度为logN的Id_Chain快速定位函数 Type Exac 指Id_Chain的同名变量
	Data_Vector* Data_Chain_Locate(int Type, int Exac, int Depth);//借由Id_Chain_Locate函数对不同深度的Data_Chain定位
	void Replace_Chain(int OldType, int OldExac, int OldDepth, int Type, int Exac);//转移Data_Chain到另一个Id_Chain下
	void Append_Chain(Data_Vector& New_Data, Id_Vector& New_Id);//链表添加内容V3 添加到Vector中
	void Get_Item_Status();//获取物品数值 并加载到结构中
	void Clear_Chain();//清理链表
	void ResetInstance();//重置Item结构的内容
	inline void OstreamSpace(std::ostream& os, int Before = 0, int After = 0);//根据级别输出空格 Before用于执行前对级别数值进行修改 After用于执行后
	inline void Combine_Status();//组合Status各物品级别并合并到Item_Instance中
public:
	TANXL_DataBase(bool Zero_Legal = false);//构造函数
	bool Get_LocalData(std::string File_Name);//获取本地数据 并新建一个链表 支持打开任意格式的文件(.usd .sd)
	//↓编辑实例 0x12345 1代表Code位 2代表Name位 3代表Oth1位 依此类推  仅在Is_Zero_Legal为false时可以正常工作
	//↓零合法时接受的十六进制数为6位 0x123456 6用于表示当前指向的位编号 范围1~5 1代表 Oth3位 2代表 Oth2位... 除最后一位以外 其余位与零不合法时完全相反
	void Set_Instance(unsigned Num, std::string Set);
	void Get_Specified(int Type, int Exac, int Nums);//读取指定Type(A)_Exac(B)级别的物品 并载入到单例结构中 Nums表示链表中的第几个(从0开始)
	//↓修改指定Type(A)_Exac(B)级别的物品 Nums表示链表中的第几个(从0开始) level取值范围为1~5 用于选定Type Exac Oth1 ...
	//↓修改OTH1 OTH2 OTH3的时候直接更改相关内容 修改TYPE-EXAC时 会转移当前Data_Chain到新的符合修改后的TYPE-EXAC的Id_Chain下
	void Set_Specified(int Type, int Exac, int Nums, int level, int Id, std::string Data);
	void Remove_Chain(int Type, int Exac);//删除某一节点与其下所有内容
	//↓输出当前内存中的链表的所有内容 仅支持输出Id_Vector和Data_Vector中的内容
	void Print_Data();
	void AppendItem(bool To_File = true, std::string File_Name = "Tanxl_DataBase.usd");//向本地文件中(.usd)添加Item物品 此函数会导致Item单例重置
	//↓使本地(.usd)文件的内容合理化 In_File_Name为输入文件名 Out_File_Name为输出文件名 现在具有保存链表修改功能
	//↓Mode为true时从文件中读取数据 需要提供In/Out_File_Name 执行后清空内存中的链表  Mode为false时直接对当前内存中的链表进行整理 可以使现有链表改为升序 执行后不清空
	void SortDataBase(int Mode = SORT_LOCALF, std::string Out_File_Name = "Tanxl_Data", std::string In_File_Name = "Tanxl_DataBase");
	friend std::ostream& operator<<(std::ostream& fot, TANXL_DataBase& s);//用于直接输出当前Item单例内的信息
};

std::string Combine_Char(std::string data, int Start, int End);//拆分char数组获取指定内容，Start为开始位置End为结束位置(结束位置不保留)

std::string Divid_Char(std::string data, int Mode = GET_STATUS_DAT);//拆分单行内容获取信息

void Reset_Chain(TANXL_DataBase TDB, int Type, int Exac, int Nums);//重置链表某一单元 Nums表示A,B level下的第几个(从0开始)

void Data(bool Mode = true, bool Zero = true);//测试用默认数据 为true时每次添加的同时还会在屏幕上打印 Zero用于选择添加模式 为True时添加的为0合法的数据

void Combine_File(std::string FileA, std::string FileB);//将FileA和FileB的内容整合到FileA中 仅限USD格式文件使用