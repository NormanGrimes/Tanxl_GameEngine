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
// 输入检测事件被观察者加入私有成员
// 移动功能采用观察者模式实现
// 移除按键观察者类的启用关闭功能和按键编号获取功能
// 最大移动距离功能代码整理优化
// 观察者模式的按键初始化替换原有的按键初始化功能
// 增加观察者模式的按键注册功能
// 原移除顶部按键事件的接口替换为移除所有观察者按键
// 移除获取已注册按键事件的个数的接口
// 观察者模式按键增加静态的移动速度倍率成员
// 设置多个按键移动速度的接口改为观察者按键模式
// 移除根据指定名称移除按键事件的接口
// 新增非移动按键观察者
// 初始化按键接口增加非移动版本重载
// 移除按键单元与按键事件类
// 取消多个按键观察者的设定
// 非移动按键使用更稳定的方案实现
// 移除旧版本按键控制长按和双击的变量
// 增加速度比率获取接口
// 鼠标点击时输出当前坐标

#pragma once

#ifndef _TANXL_INSERTACTION_
#define _TANXL_INSERTACTION_

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
	MOVETO_NONE,
	MOVETO_PARA,
	MOVETO_VERT,
	MOVETO_BOTH
};

class Key_Observer : public Event_Observer<int>
{
public:
	Key_Observer(int GLFW_KEY, MoveTo_Direction Direction, float Move_Length, Tanxl_Coord <float>* Target) :
		_GLFW_KEY(GLFW_KEY), _Direction(Direction), _Move_Length(Move_Length), _Target(Target) {}

	virtual void EventCheck(int& Event)
	{
		if (Event == this->_GLFW_KEY)
		{
			//std::cout << "Event Call : " << this->_GLFW_KEY << std::endl;
			if (this->_Direction == MoveTo_Direction::MOVETO_PARA)
				this->_Target->_Coord_X += this->_Move_Length * _Speed_Rato;
			if (this->_Direction == MoveTo_Direction::MOVETO_VERT)
				this->_Target->_Coord_Y += this->_Move_Length * _Speed_Rato;
			if (this->_Direction == MoveTo_Direction::MOVETO_BOTH)
				*this->_Target += this->_Move_Length * _Speed_Rato;
		}
	}

	static void Set_Speed_Ratio(float Speed_Rato)
	{
		_Speed_Rato = Speed_Rato;
	}

	static float Get_Speed_Ratio()
	{
		return _Speed_Rato;
	}

private:
	int _GLFW_KEY;
	MoveTo_Direction _Direction;
	float _Move_Length;
	static float _Speed_Rato;

	Tanxl_Coord<float>* _Target;
};

class Press_Observer : public Event_Observer<int>
{
public:
	Press_Observer(int GLFW_KEY, bool* BindStatus) :
		_Internal_UnPress_Count(0), _Internal_Press_Count(0), _GLFW_KEY(GLFW_KEY), _Event_Processed(false), _KeyPressed(BindStatus) {}

	virtual void EventCheck(int& Event)
	{
		if (Event == this->_GLFW_KEY)
		{
			this->_Internal_Press_Count++;
			this->_Internal_UnPress_Count = 0;
			if ((this->_Internal_Press_Count > 2) && (this->_Event_Processed == false))
			{
				this->_Event_Processed = true;
				*this->_KeyPressed = true;
			}
		}
		else
		{
			this->_Internal_UnPress_Count++;
			if (this->_Internal_UnPress_Count > 4)
			{
				this->_Event_Processed = false;
				this->_Internal_Press_Count = 0;
			}
		}
	}

private:
	int _Internal_UnPress_Count;
	int _Internal_Press_Count;
	int _GLFW_KEY;
	bool _Event_Processed;
	bool* _KeyPressed;
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
	//检测是否有按键按下
	bool Check_Key_Press(GLFWwindow* Window);
	//获取到当前移动操作是否导致移动到地图边缘
	short Get_Reach_Edge() const;
	unsigned Get_Insert_Status() const;
	const std::string Get_Version();
	//移除最近一个添加的按键功能
	Tanxl_Coord<double> Get_Mouse_Location() const;
	void RemoveAllEvent();
	//注册一个按键功能 使之能够在窗口中反应 如果仅定义按键而不注册则不会产生任何效果
	void RegistEvent(int GLFW_KEY, MoveTo_Direction MOVETO_VERT, float Move_Length);
	void RegistEvent(int GLFW_KEY, bool* BindStatus);
	//获取键盘输入 window为需要获取输入的OpenGL窗口 State为需要操作的地图 支持非移动按钮功能
	//获取到输入后不会立刻执行移动操作 仅记录移动距离 通过地图模块的更新移动功能执行移动操作
	void GetInsert(GLFWwindow* window, GameStateBase* State, GameObject& Character);
	//获取鼠标输入
	void GetMouseInput(GLFWwindow* window);
	//Max_float用于指定最大移动距离（相对地图比例）设置当前操作可移动到的高/宽度方向最远距离
	//此功能仅在所有区域均为正方形时可以正常使用 否则可能导致部分空间抵达显示区域外
	void Set_MaxFloat(float Max_floatX, float Max_floatY = 0.0f);
	//设置移动操作是否会导致方块移动到地图外 State_Range的值默认为真 为真时无法移动到地图外
	void Set_StateRange(bool Enable);
	//同时设置多个按键控制的移动距离
	void Set_MultiSpeed(double Adjust_Value);
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
	//_KeyNameS 所有已注册输入事件名称的容器
	std::vector<int> _KeyNameS;
	//_Is_Reach_Edge 用于标记当前移动操作是否到达了地图边缘 0为未到达边缘 1为左边缘 2为右边缘 3为上边缘 4为下边缘
	short _Is_Reach_Edge{ 0 };
	//_Insert_Status 第二版移动状态变量 包含更多状态
	unsigned _Insert_Status{ 0 };
	//_Is_State_Range 用于标记当前是否限制了移动范围
	bool _Is_State_Range;
	//_Is_Key_Pressed 用于标记当前是否按下了按键
	bool _Is_Key_Pressed;
	//_Is_Key_Enable 用于标记当前是否响应输入
	bool _Is_Key_Enable;
	//_Insert_Move_Length 记录当前输入导致的移动距离
	Tanxl_Coord<float> _Insert_Move_Length{ 0.0f, 0.0f };
	//_Maximum_Distance 代表当前主控制物品在X/Y轴的最大移动距离
	Tanxl_Coord<float> _Maximum_Distance{ 1.0f, 1.0f };
	//_Mouse_PosX 记录当前鼠标的X/Y轴坐标
	Tanxl_Coord<double> _Mouse_Pos{ 0, 0 };
	//_InsertCheck 输入检测的被观察者
	EventSubject<int> _InsertCheck;
	//单例实现部分
	InsertEventBase();
	~InsertEventBase();
	InsertEventBase(const InsertEventBase&);
	InsertEventBase& operator=(const InsertEventBase&);
};

#endif