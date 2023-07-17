//_VERSION_0_7_ UPDATE LOG
// LAST_UPDATE 2022-12-28 11:31
// 调整部分变量名称
// 修复输入操作物品移动与地图偏移不一致的问题
// 按键单元结构体增加名称成员
// 提供删除指定名称的输入按键功能
// 提供标记移动到地图边缘的相关功能
// 修复按键单元初始化时未正确初始化NAME的问题
// 增加版本变量与获取接口
// 增加获取某一按键是否按下的判断函数
// 移除未使用且意义不明的_Max_Line变量
// 移除CheckInsert接口（功能重复）
// 增加宏来控制控制台输出的开启与关闭
// 是否到达边缘的标记改为short类型且获取函数改为线程安全式
// 修复边缘标记不标记符号小于的问题
// 修复边缘标记上方边缘错误的问题
// 指针初始化采用nullptr替代NULL
// 输入操作的执行步骤延迟到完整检测之后
// 修复输入操作最后一个操作执行错误的问题
// AutoCheck接口移除两个未使用入参
// GetInsert接口移除四个不需要的入参
// AutoCheck接口取消地图移动并优化为不返回值

#pragma once

#ifndef _TANXL_INSERTACTION_
#define _TANXL_INSERTACTION_

#define _TANXL_INSERTACTION_CONSOLE_OUTPUT_

#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include "Tanxl_UniqueID.h"

struct Key_Unit
{
	Key_Unit();
	Key_Unit(int GLKEY, bool MOVX, bool MOVY, double MOVL, std::string UNAM = "");
	Key_Unit(int GLKEY, bool* CustomX = nullptr, bool* CustomY = nullptr, std::string UNAM = "");

	//用于标记当前按键的类型
	short Unit_Type;
	//用于记录触发事件需要的按键
	int   GLFW_KEY;
	//用于标记此按键是否会导致向X轴方向移动
	bool  MoveToX;
	//用于标记此按键是否会导致向Y轴方向移动
	bool  MoveToY;
	//用于记录按键操作可能导致的移动距离
	double MoveLen;
	//用于记录按键事件的名称
	std::string Unit_Name;
};

class InsertEventBase
{
public:
	//获取输入模块的单例类
	static InsertEventBase& GetInsertBase();
	//自动根据已知信息返回方块能移动的最大范围 公式 1 - ( 1 / 游戏地图边长（方块数）)
	float Get_AutoFloat(int Blocks);
	float Get_Margin_X();
	float Get_Margin_Y();
	//获取当前是否按下了按键 并重置此变量状态为未按下
	bool Get_Key_Pressed();
	//删除指定名称的输入按键功能
	bool RemoveEvent(std::string Event_Name);
	//获取到当前移动操作是否导致移动到地图边缘 调用后会重置成员内容为否
	short Get_Reach_Edge();
	const std::string Get_Version();
	//注册一个按键功能 使之能够在窗口中反应 如果仅定义按键而不注册则不会产生任何效果
	void RegistEvent(Key_Unit* KU);
	//移除最近一个添加的按键功能
	void RemoveEvent();
	void GetInsert(GLFWwindow* window, float& MoveX, float& MoveY);
	//地图边长相同时 或仅允许在一个正方形区域移动时使用 Max_float用于指定最大移动距离（相对地图比例）
	//此功能仅在所有区域均为正方形时可以正常使用 否则可能导致部分空间抵达显示区域外
	//在使用后会导致Set_MaxFloat_Height/Width功能无效化
	void Set_MaxFloat(float Max_float);
	//设置当前操作可移动到的高度方向最远距离 在使用后会导致Set_MaxFloat功能无效化 可在边长不规则情况下使用
	void Set_MaxFloat_Height(float Max_float);
	//设置当前操作可移动到的宽度方向最远距离 在使用后会导致Set_MaxFloat功能无效化 可在边长不规则情况下使用
	void Set_MaxFloat_Width(float Max_float);
	void Get_MoveData(std::vector<bool>* PVB);
	//设置移动操作是否会导致方块移动到地图外 State_Range的值默认为真 为真时无法移动到地图外
	void Set_StateRange(bool Enable);
private:
	void AutoCheck(float* MoveX, float* MoveY);
	std::vector<Key_Unit*> _KeyEventS;
	std::vector<bool>* _PTB;
	//_Max_float 用于记录在移动过程中能够移动到的距中心X/Y轴最远距离
	float _Max_float;
	//_Is_Reach_Edge 用于标记当前移动操作是否到达了地图边缘 0为未到达边缘 1为左边缘 2为右边缘 3为上边缘 4为下边缘
	short _Is_Reach_Edge = 0;
	//_Is_State_Range 用于标记当前是否限制了移动范围
	bool _Is_State_Range;
	//_Is_Max_Single 用于标记当前是否使用单一X/Y轴设置方式
	bool _Is_Max_Single;
	//_Is_Key_Pressed 用于标记当前是否按下了按键
	bool _Is_Key_Pressed;
	//_Margin_X 代表当前主控制物品最近一次移动的X坐标移动距离
	float _Margin_X;
	//_Margin_Y 代表当前主控制物品最近一次移动的Y坐标移动距离
	float _Margin_Y;
	//_Max_float_Height 代表当前主控制物品在Y轴的最大移动距离
	float _Max_float_Height;
	//_Max_float_Width  代表当前主控制物品在X轴的最大移动距离
	float _Max_float_Width;
	//_Version 用于记录当前程序（输入模块-InserAction）的版本信息
	const std::string _Version{ "0.7" };
	//单例实现私有构造函数
	InsertEventBase();
	~InsertEventBase();
	InsertEventBase(const InsertEventBase&);
	InsertEventBase& operator=(const InsertEventBase&);
};

#endif