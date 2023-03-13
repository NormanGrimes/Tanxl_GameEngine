//_VERSION_0_5_ UPDATE LOG
// LAST_UPDATE 2022-10-04 21:16
// �Ż�����������ѭ���Ĵ�����
// �Ż�ReLoadState�����ж�
// �޸�һ�������߼��жϴ���
// �Ƴ����ƽ׶����������ͼ�Ķ����ж�
// �����Ż�����ÿ��ѭ������Ҫ���ж�
// ����ģ�齫����ѭ����Ϊһ�λ���

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
	void Render_Once(GameStateBase* State);
	void UpdateMargin(float& Margin);
	void Set_PreLoad(int PreLoads);
	void Set_WaitFra(int First_Adjust);
	//���ڵ�һ�λ����¼���������ͼ����
	void ReLoadState(GameStateBase* State);
private:

	GLuint _Position;

	GLint _StateInfor[201];

	bool _Clear_Function;
	bool _Is_State_Changed;

	GLuint _renderingProgram;
	GLuint _vao[1];

	//��¼��ͼ����X���ƶ�����
	float _State_MoveX;
	//��¼��ͼ����Y���ƶ�����
	float _State_MoveY;

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
	//����ģ���Զ������ȴ�֡
	int _First_Adjust;
	GLFWwindow* _Main_Window;
};