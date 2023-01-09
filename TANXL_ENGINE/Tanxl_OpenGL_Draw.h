//_VERSION_0_4_ UPDATE LOG
// LAST_UPDATE 2022-09-15 21:45
// 修复重新载入地图功能无符号数与有符号数比较可能导致的问题
// 自动移动背景功能修改入参并加入对多处坐标的修改
// 根据State模块调整标记对场景反向加载

#pragma once

#ifndef TANXL_DATABASE_H
#define TANXL_DATABASE_H
#include "Tanxl_DataBase.h"
#endif

#ifndef TANXL_GAMESTATE_H
#define TANXL_GAMESTATE_H
#include "Tanxl_GameState.h"
#endif

#ifndef TANXL_INSERTACTION_H
#define TANXL_INSERTACTION_H
#include "Tanxl_InsertAction.h"
#endif

#ifndef TANXL_OPENGL_RENDER_H
#define TANXL_OPENGL_RENDER_H
#include "Tanxl_OpenGL_Render.h"
#endif

#ifndef TANXL_UNIQUEID
#define TANXL_UNIQUEID
#include "Tanxl_UniqueID.h"
#endif

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

class OpenGL_Draw
{
public:
	OpenGL_Draw(int ScreenWidth = 600, int ScreenHeight = 600);
	//绘制模块主要初始化函数 window为需要绘制的窗口 State为单例类，需要完成地图设置后再调用此函数初始化
	void init(GLFWwindow* window, GameStateBase* State);
	void display(GLFWwindow* window, double currentTime, GameStateBase* State);
	//绘制主循环 在此之后的一切操作都会被忽略
	void mainLoop(GameStateBase* State);
	void UpdateMargin(float& Margin);
	void Set_PreLoad(int PreLoads);
	//用于第一次或重新加载整个地图场景
	void ReLoadState(GameStateBase* State, int PosX, int PosY);
private:

	GLuint _Position;

	GLint _StateInfor[201];

	bool _Clear_Function;
	bool _Is_State_Changed;

	GLuint _renderingProgram;
	GLuint _vao[1];

	//记录地图场景的方块行数
	int _HeightInt;
	//记录地图场景的方块列数
	int _WidthInt;
	//窗口的宽度
	int _ScreenWidth;
	//窗口的高度
	int _ScreenHeight;
	//记载额外加载的地图环数量
	int _PreLoads;
};