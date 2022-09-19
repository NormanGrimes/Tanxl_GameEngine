//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-07-24 16:28
// �����Ľ�����Ϊ0.00.00.10�汾
// ɾ����������Ҫ��˽�б���
// �ӳ�ʼ���������������ͼ���뺯��

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
	//���ڵ�һ�λ����¼���������ͼ����
	void ReLoadState(GameStateBase* State);
private:

	GLuint _Position;

	GLint _StateInfor[201];

	bool _Clear_Function = false;

	GLuint _renderingProgram;
	GLuint _vao[1];

	//��¼��ͼ�����ķ�������
	int _HeightInt;
	//��¼��ͼ�����ķ�������
	int _WidthInt;
	
	int _ScreenWidth;
	int _ScreenHeight;
};