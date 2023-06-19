//_VERSION_0_8_ UPDATE LOG
// LAST_UPDATE 2023-01-16 17:40
// 纹理功能已调试完成并实装
// 移除构造函数的默认参数
// 代码删除部分冗余 等待下一次优化
// 增加地图背景随着移动操作而移动的功能

#pragma once

#ifndef _TANXL_OPENGL_DRAW_
#define _TANXL_OPENGL_DRAW_

#include "Tanxl_DataBase.h"
#include "Tanxl_GameState.h"
#include "Tanxl_InsertAction.h"
#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_UniqueID.h"
#include "SOIL2/SOIL2.h"
#include <math.h>

class OpenGL_Draw
{
public:
	static OpenGL_Draw& GetOpenGLBase(int ScreenWidth = 800, int ScreenHeight = 800);
	
	const std::string Get_Version();
	//绘制模块主要初始化函数 window为需要绘制的窗口 State为单例类，需要完成地图设置后再调用此函数初始化
	void init(GLFWwindow* window, GameStateBase* State);
	void display(GLFWwindow* window, double currentTime, GameStateBase* State);
	//绘制主循环 在此之后的一切操作都会被忽略
	void Render_Once(GameStateBase* State);
	void UpdateMargin(float& Margin);
	void Set_PreLoad(int PreLoads);
	void Set_WaitFra(int First_Adjust);
	void Set_Clear(bool Clear);
	void Set_Trigger_Range(bool Enable, float Height, float Width);
	EMove_State_EventId Auto_Update_Trigger(float Height, float Width);
	//用于第一次或重新加载整个地图场景
	void ReLoadState(GameStateBase* State);
	GLFWwindow* Get_Window()const;
private:
	OpenGL_Draw(int ScreenWidth, int ScreenHeight);

	GLint _StateInfor[200];

	bool _Clear_Function;
	bool _Is_State_Changed;
	//标记是否启用地图随移动而移动的功能
	bool _Is_Trigger_Enable = false;

	GLuint _renderingProgram;
	GLuint _vao[1];

	//记录地图场景基本矩形的高度值
	double _Each_Height = 0;
	//记录地图场景基本矩形的宽度值
	double _Each_Width = 0;

	//记录地图场景X轴移动距离
	float _State_MoveX;
	//记录地图场景Y轴移动距离
	float _State_MoveY;
	//记录自动调整状态的X轴移动距离
	float _Auto_AdjustX = 0.0f;
	//记录自动调整状态的Y轴移动距离
	float _Auto_AdjustY = 0.0f;
	//记录手动移动状态的Y轴移动距离
	float _Move_AdjustX = 0.0f;
	//记录手动移动状态的Y轴移动距离
	float _Move_AdjustY = 0.0f;
	//触发地图移动事件时的最低高度方向移动距离
	float _Trigger_Height = 1.0f;
	//触发地图移动事件时的最低宽度方向移动距离
	float _Trigger_Width  = 1.0f;
	//记录地图场景的基本矩形行数
	int _HeightInt;
	//记录地图场景的基本矩形列数
	int _WidthInt;
	//窗口的宽度
	int _ScreenWidth;
	//窗口的高度
	int _ScreenHeight;
	//记载额外加载的地图环数量
	int _PreLoads;
	//绘制模块自动调整等待帧
	int _First_Adjust;
	//记录手动移动指定的当前X轴基本矩形
	int _Current_Move_Height = 0;
	//记录手动移动指定的当前Y轴基本矩形
	int _Current_Move_Width = 0;
	const std::string _Version{ "0.8" };
	GLFWwindow* _Main_Window;
};

#endif