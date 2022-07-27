//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-09 00:03
// 成功解决深度测试技术难题，现在支持多层次显示
// 修复地图数据传输错误的问题
// 额外绘制一个方块用于铺满屏幕
// 整合至类中 隐藏所有全局变量

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

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

const int numVAOs = 1;


class OpenGL_Draw
{
public:
	void init(GLFWwindow* window, GameStateBase* State) {
		//示例提供四个按键操作事件
		srand(static_cast<unsigned int>(time(0)));

		for (int i = 0; i < 101; i++)
			StateInfor[i] = rand() % 2 - 1;

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(1.0f);

		HeightInt = State->GetStateHeight();
		WidthInt = State->GetStateWidth();
		renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
		glGenVertexArrays(numVAOs, vao);
		glBindVertexArray(vao[0]);
		Height = glGetUniformLocation(renderingProgram, "SHeight");
		glProgramUniform1f(renderingProgram, Height, static_cast<float>(HeightInt));
		Width = glGetUniformLocation(renderingProgram, "SWidth");
		glProgramUniform1f(renderingProgram, Width, static_cast<float>(WidthInt));
		for (int i = 0; i < HeightInt * WidthInt + 1; i++)
		{
			StateInfor[i];
		}
		GLuint StatePos[101]{};
		for (int i = 0; i < HeightInt * WidthInt + 1; i++)
		{
			std::string Tag = "State[" + std::to_string(i) + "]";
			StatePos[i] = glGetUniformLocation(renderingProgram, Tag.c_str());
			glProgramUniform1i(renderingProgram, StatePos[i], StateInfor[i]);
		}
	}

	void display(GLFWwindow* window, double currentTime) {

		if (Clear_Function)
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		float SinCurrent = static_cast<float>(sin(currentTime)) * 0.5f;
		float CosCurrent = static_cast<float>(cos(currentTime)) * 0.5f;

		PosA = glGetUniformLocation(renderingProgram, "SinCurrentTime");
		glProgramUniform1f(renderingProgram, PosA, SinCurrent);
		PosB = glGetUniformLocation(renderingProgram, "CosCurrentTime");
		glProgramUniform1f(renderingProgram, PosB, CosCurrent);

		glUseProgram(renderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, HeightInt * WidthInt * 6 + 6);
	}

	int mainLoop(GameStateBase* State)
	{
		if (!glfwInit()) { exit(EXIT_FAILURE); }
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		GLFWwindow* window = glfwCreateWindow(600, 600, "Tanxl_Game TEST VERSION /// 0.00.00.09", NULL, NULL);
		glfwMakeContextCurrent(window);
		if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
		glfwSwapInterval(1);

		init(window, State);

		while (!glfwWindowShouldClose(window))
		{
			glClearDepth(1.0f);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			PosX = glGetUniformLocation(renderingProgram, "MoveX");//更新操作物品坐标
			glProgramUniform1f(renderingProgram, PosX, movex);
			PosY = glGetUniformLocation(renderingProgram, "MoveY");
			glProgramUniform1f(renderingProgram, PosY, movey);

			IEB->GetInsert(window, &movex, &movey);

			display(window, glfwGetTime());
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
private:

	GLuint PosA, PosB;
	GLuint PosX, PosY;
	GLuint Height, Width;

	GLint StateInfor[101];

	bool Clear_Function = false;

	float movex;
	float movey;

	GLuint renderingProgram;
	GLuint vao[numVAOs];

	int HeightInt;
	int WidthInt;

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
};