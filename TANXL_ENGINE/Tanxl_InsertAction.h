//_VERSION_0_9_ UPDATE LOG
// LAST_UPDATE 2023-12-05 15:17
// 简化检测输入功能中数值计算部分
// 增加鼠标坐标的设置与获取接口
// 更新最大移动距离的接口不再依赖绘制模块进行更新
// 自动检测接口参数简化
// 上次移动距离的记录移入地图模块
// 多个成员函数设为常量
// 获取鼠标位置的函数设为静态函数
// 设置最大移动范围功能整合进输入模块
// 预增加第二版按键单元的定义
// 加入上次输入导致的移动方向的记录
// 增加第二版输入状态量测试
// 修改按键对应的输入状态
// 移除第一版移动状态量
// 增加按键移动方向的枚举
// 按键观察者类优化改进
// 增加按键观察者模式的测试

#pragma once

#ifndef _TANXL_INSERTACTION_
#define _TANXL_INSERTACTION_

#define _ENABLE_TANXL_INSERTACTION_OBSERVER_TEST_  1
#define _ENABLE_TANXL_INSERTACTION_CONSOLE_OUTPUT_ 0

#if _ENABLE_TANXL_INSERTACTION_CONSOLE_OUTPUT_

#define _TANXL_INSERTACTION_CONSOLE_BASE_OUTPUT_   0
#define _TANXL_INSERTACTION_CONSOLE_RANDOM_OUTPUT_ 0
#define _TANXL_INSERTACTION_CONSOLE_AUTO_OUTPUT_   0
#define _TANXL_INSERTACTION_CONSOLE_MOUSE_OUTPUT_  1

#endif

#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Tanxl_OpenGL_Draw.h"
#include "Tanxl_GameState.h"
#include "Tanxl_RandomBase.h"
#include "Tanxl_GameTips.h"
#include "Tanxl_EngineBase.h"
#include "Tanxl_LocationBase.h"
#include "Tanxl_GameEvent.h"

enum MoveTo_Direction
{
	MOVETO_PARA,
	MOVETO_VERT,
	MOVETO_BOTH
};

class Key_Observer :public Event_Observer<int>
{
public:
	Key_Observer(int GLFW_KEY, MoveTo_Direction Direction, float Move_Length) :
		_GLFW_KEY(GLFW_KEY), _Enable(true), _Direction(Direction), _Move_Length(Move_Length) {}

	virtual void EventCheck(int& Event)
	{
		if (Event)
		{
			if (Event == _GLFW_KEY)
				std::cout << "Key Event Call : " << _GLFW_KEY << std::endl;
		}
	}

	void Enable(bool Enable)
	{
		this->_Enable = Enable;
	}

	int Get_GLKey() const
	{
		return this->_GLFW_KEY;
	}

private:
	int _GLFW_KEY;
	bool _Enable;
	MoveTo_Direction _Direction;
	float _Move_Length;
};

struct Key_Unit
{
	Key_Unit();
	Key_Unit(int GLKEY, bool MOVX, bool MOVY, double MOVL, std::string UNAM = "");
	Key_Unit(int GLKEY, std::string UNAM = "");

	bool Get_KeyStatus() const;

	//用于标记当前按键的类型
	short Unit_Type;
	//用于记录触发事件需要的按键
	int   GLFW_KEY;
	//用于标记此按键是否会导致向X轴方向移动
	bool  MoveToX;
	//用于标记此按键是否会导致向Y轴方向移动 同时在按键模式下为按键的TRUE\FALSE两个状态 每次按下按键都会切换状态
	bool  MoveToY;
	//用于记录按键操作可能导致的移动距离
	double MoveLen;
	//用于记录移动距离
	double SaveLen;
	//用于记录按键事件的名称
	std::string Unit_Name;
};

struct Key_Event
{
	Key_Event(Key_Unit* Key);

	Key_Unit* _Key_Unit;
	bool _Is_Key_Press;
	int _Press_Count;
};

class InsertEventBase : public Tanxl_ClassBase
{
public:
	//获取输入模块的单例类
	static InsertEventBase& GetInsertBase();
	//自动根据已知信息返回方块能移动的最大范围 公式 1 - ( 1 / 游戏地图边长（方块数）)
	float Get_AutoFloat(int Blocks);
	//获取当前是否按下了按键 并重置此变量状态为未按下
	bool Get_Key_Pressed();
	//删除指定名称的输入按键功能
	bool RemoveEvent(std::string Event_Name);
	//检测是否有按键按下
	bool Check_Key_Press(GLFWwindow* Window);
	//获取到当前移动操作是否导致移动到地图边缘
	short Get_Reach_Edge() const;
	unsigned Get_Insert_Status() const;
	const std::string Get_Version();
	//注册一个按键功能 使之能够在窗口中反应 如果仅定义按键而不注册则不会产生任何效果
	int RegistEvent(Key_Unit* KU);
	//移除最近一个添加的按键功能
	Tanxl_Coord<double> Get_Mouse_Location() const;
	void RemoveEvent();
	size_t Get_KeyEvent_Size();
	//获取键盘输入 window为需要获取输入的OpenGL窗口 State为需要操作的地图 支持非移动按钮功能
	//获取到输入后不会立刻执行移动操作 仅记录移动距离 通过地图模块的更新移动功能执行移动操作
	void GetInsert(GLFWwindow* window, GameStateBase* State, GameObject& Character);
	//获取鼠标输入
	void GetMouseInput(GLFWwindow* window);
	//地图边长相同时 或仅允许在一个正方形区域移动时使用 Max_float用于指定最大移动距离（相对地图比例）
	//此功能仅在所有区域均为正方形时可以正常使用 否则可能导致部分空间抵达显示区域外
	//在使用后会导致Set_MaxFloat_Height/Width功能无效化
	void Set_MaxFloat(float Max_float);
	//设置当前操作可移动到的高度方向最远距离 在使用后会导致Set_MaxFloat功能无效化 可在边长不规则情况下使用
	void Set_MaxFloat_Height(float Max_float);
	//设置当前操作可移动到的宽度方向最远距离 在使用后会导致Set_MaxFloat功能无效化 可在边长不规则情况下使用
	void Set_MaxFloat_Width(float Max_float);
	//设置移动操作是否会导致方块移动到地图外 State_Range的值默认为真 为真时无法移动到地图外
	void Set_StateRange(bool Enable);
	//同时设置多个按键控制的移动距离
	void Set_MultiSpeed(int Start, int End, double Adjust_Value);
	void Set_Key_Enable(bool Enable);
	// 初始化默认提供的八个移动按键
	void Init_Default_Key();
	void Set_Mouse_Pos(double LocationX, double LocationY);
	// 设置触发地图移动事件时的方向移动距离占总距离的比率
	void Set_Trigger_Range(float Ratio);
	void Reset_Move_Range();
private:
	//对输入获取之后的数据进行各项限制的检查 如超出移动距离最大值则会将其限制到最大值 同时记录是否抵达屏幕边缘
	void AutoCheck(Tanxl_Coord<float>& Screen_Move, Tanxl_Coord<float>& Move_Distance);
	//_KeyEventS 所有已注册输入事件的容器
	std::vector<Key_Event*> _KeyEventS;
	//_Max_float 用于记录在移动过程中能够移动到的距中心X/Y轴最远距离
	float _Max_float;
	//_Is_Reach_Edge 用于标记当前移动操作是否到达了地图边缘 0为未到达边缘 1为左边缘 2为右边缘 3为上边缘 4为下边缘
	short _Is_Reach_Edge{ 0 };
	//_Insert_Status 第二版移动状态变量 包含更多状态
	unsigned _Insert_Status{ 0 };
	//_Is_State_Range 用于标记当前是否限制了移动范围
	bool _Is_State_Range;
	//_Is_Max_Single 用于标记当前是否使用单一X/Y轴设置方式
	bool _Is_Max_Single;
	//_Is_Key_Pressed 用于标记当前是否按下了按键
	bool _Is_Key_Pressed;
	//_Is_Key_Enable 用于标记当前是否响应输入
	bool _Is_Key_Enable;
	//_Max_float_Height 代表当前主控制物品在Y轴的最大移动距离
	float _Max_float_Height;
	//_Max_float_Width 代表当前主控制物品在X轴的最大移动距离
	float _Max_float_Width;
	//_Key_Press_Length 记录一个按键事件确认按下需要的帧数
	double _Key_Press_Length{ 10 };
	//_Key_Extra_Press 记录一个按键事件重复执行按下操作需要的帧数
	double _Key_Extra_Press{ 20 };
	//_Mouse_PosX 记录当前鼠标的X/Y轴坐标
	Tanxl_Coord<double> _Mouse_Pos{ 0, 0 };
	//单例实现部分
	InsertEventBase();
	~InsertEventBase();
	InsertEventBase(const InsertEventBase&);
	InsertEventBase& operator=(const InsertEventBase&);
};

#endif