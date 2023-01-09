//_VERSION_0_4_ UPDATE LOG
// LAST_UPDATE 2022-09-15 21:45
// �޸����������ͼ�����޷��������з������ȽϿ��ܵ��µ�����
// �Զ��ƶ����������޸���β�����Զദ������޸�
// ����Stateģ�������ǶԳ����������

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
	//����ģ����Ҫ��ʼ������ windowΪ��Ҫ���ƵĴ��� StateΪ�����࣬��Ҫ��ɵ�ͼ���ú��ٵ��ô˺�����ʼ��
	void init(GLFWwindow* window, GameStateBase* State);
	void display(GLFWwindow* window, double currentTime, GameStateBase* State);
	//������ѭ�� �ڴ�֮���һ�в������ᱻ����
	void mainLoop(GameStateBase* State);
	void UpdateMargin(float& Margin);
	void Set_PreLoad(int PreLoads);
	//���ڵ�һ�λ����¼���������ͼ����
	void ReLoadState(GameStateBase* State, int PosX, int PosY);
private:

	GLuint _Position;

	GLint _StateInfor[201];

	bool _Clear_Function;
	bool _Is_State_Changed;

	GLuint _renderingProgram;
	GLuint _vao[1];

	//��¼��ͼ�����ķ�������
	int _HeightInt;
	//��¼��ͼ�����ķ�������
	int _WidthInt;
	//���ڵĿ��
	int _ScreenWidth;
	//���ڵĸ߶�
	int _ScreenHeight;
	//���ض�����صĵ�ͼ������
	int _PreLoads;
};