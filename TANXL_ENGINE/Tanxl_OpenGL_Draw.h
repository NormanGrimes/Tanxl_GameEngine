//_VERSION_0_7_ UPDATE LOG
// LAST_UPDATE 2022-12-28 11:29
// 修复重新加载功能可能导致多段移动只计算一段加载的问题
// 修复地图绘制展示错误区块的问题
// 修复在移动时调整开启时移动操作不会触发重新载入的问题
// 删除_Position采用固定位置获取统一变量
// Move_Adjust归入私有成员变量
// 增加清屏设置函数
// 自动调整丢弃的值加入绘制移动

#pragma once

#ifndef _TANXL_OPENGL_DRAW_
#define _TANXL_OPENGL_DRAW_

#include "Tanxl_DataBase.h"
#include "Tanxl_GameState.h"
#include "Tanxl_InsertAction.h"
#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_UniqueID.h"
#include <math.h>

class OpenGL_Draw
{
public:
	static OpenGL_Draw& GetOpenGLBase(int ScreenWidth = 800, int ScreenHeight = 800);
	
	//绘制模块主要初始化函数 window为需要绘制的窗口 State为单例类，需要完成地图设置后再调用此函数初始化
	void init(GLFWwindow* window, GameStateBase* State);
	void display(GLFWwindow* window, double currentTime, GameStateBase* State);
	//绘制主循环 在此之后的一切操作都会被忽略
	void Render_Once(GameStateBase* State);
	void UpdateMargin(float& Margin);
	void Set_PreLoad(int PreLoads);
	void Set_WaitFra(int First_Adjust);
	void Set_Clear(bool Clear);
	//用于第一次或重新加载整个地图场景
	void ReLoadState(GameStateBase* State);
private:
	OpenGL_Draw(int ScreenWidth = 600, int ScreenHeight = 600);

	GLint _StateInfor[200];

	bool _Clear_Function;
	bool _Is_State_Changed;

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

	GLFWwindow* _Main_Window;
};

#endif