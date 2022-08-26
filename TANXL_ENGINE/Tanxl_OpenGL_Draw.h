//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-05-28 01:49
// 同意义变量复用 移除两个成员变量
// 整理至引擎核心层
// 暂时禁用片段着色器的功能
// 修复存在一个空循环的问题
// 优化去掉大量中间变量

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
	void init(GLFWwindow* window, GameStateBase* State);
	void display(GLFWwindow* window, double currentTime);
	//绘制主循环 在此之后的一切操作都会被忽略
	void mainLoop(GameStateBase* State);
	void UpdateMargin(float& Margin);
private:

	GLuint Position;

	GLint StateInfor[201];

	bool Clear_Function = false;

	float _MoveX;
	float _MoveY;

	GLuint renderingProgram;
	GLuint vao[1];

	int HeightInt;
	int WidthInt;
	
	int _ScreenWidth;
	int _ScreenHeight;
};