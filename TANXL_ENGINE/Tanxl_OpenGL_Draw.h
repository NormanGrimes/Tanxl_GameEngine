//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-05-28 01:49
// ͬ����������� �Ƴ�������Ա����
// ������������Ĳ�
// ��ʱ����Ƭ����ɫ���Ĺ���
// �޸�����һ����ѭ��������
// �Ż�ȥ�������м����

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
	//������ѭ�� �ڴ�֮���һ�в������ᱻ����
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