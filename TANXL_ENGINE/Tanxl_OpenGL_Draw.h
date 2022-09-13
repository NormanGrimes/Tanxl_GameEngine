//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-07-24 16:28
// 因大幅改进整理为0.00.00.10版本

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

	GLuint _Position;

	GLint _StateInfor[201];

	bool _Clear_Function = false;

	float _MoveX;
	float _MoveY;

	GLuint _renderingProgram;
	GLuint _vao[1];

	int _HeightInt;
	int _WidthInt;
	
	int _ScreenWidth;
	int _ScreenHeight;
};