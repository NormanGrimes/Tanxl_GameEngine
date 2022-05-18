//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-04-27 22:32
// »ù´¡°æ±¾

#ifndef GL_GLEW_H
#define GL_GLEW_H
#include <GL\glew.h>
#endif


#include <GLFW\glfw3.h>
#include <string>
#include <queue>
#include <vector>

enum EDIR
{
	EDIR_MOVE_UP    = 0,
	EDIR_MOVE_DOWN  = 1,
	EDIR_MOVE_LEFT  = 2,
	EDIR_MOVE_RIGHT = 3,
};

struct KeyUnit
{
public:
	KeyUnit(int GL_Defines, std::string Names, float Speed, int Direct) :
		Name(Names), GL_Define(GL_Defines), speed(Speed), Direction(Direct) {}

	int GL_Define;
	std::string Name;
	int Direction;
	float speed;
};

//Default Data
KeyUnit UP   (GLFW_KEY_UP,    "MOVUP",    0.01f, EDIR_MOVE_UP);
KeyUnit DOWN (GLFW_KEY_DOWN,  "MOVDOWN",  0.01f, EDIR_MOVE_DOWN);
KeyUnit LEFT (GLFW_KEY_LEFT,  "MOVLEFT",  0.01f, EDIR_MOVE_LEFT);
KeyUnit RIGHT(GLFW_KEY_RIGHT, "MOVRIGHT", 0.01f, EDIR_MOVE_RIGHT);

class KeyEventBase
{
public:

	bool RegistInsert(KeyUnit* PTKU)
	{
		std::string TempName{ PTKU->Name };
		for (int i = 0; i < KeyUnits.size(); i++)
		{
			if (KeyUnits.at(i)->Name == TempName)
				return false;
		}
		KeyUnits.push_back(PTKU);
		return true;
	}

	static KeyEventBase& GetKeyEventBase(float* PTX, float* PTY, float* PTM)
	{
		static KeyEventBase KEB(PTX, PTY, PTM);
		return KEB;
	}

	void GetKeys(GLFWwindow* window)
	{
		for (int i = 0; i < KeyUnits.size(); i++)
		{
			if (glfwGetKey(window, KeyUnits.at(i)->GL_Define) == GLFW_PRESS)
			{
				InsertStack.push(KeyUnits.at(i));
				std::cout << "PUSHED! " << std::endl;
				return;
			}
		}
	}

	void ProcessKeys()
	{
		while (InsertStack.size() != 0)
		{
			std::string Temp{ InsertStack.front()->Name };
			int count{ 0 };
			while (InsertStack.front()->Name == Temp)
			{
				count++;
				if (count >= 5)
				{
					count = 0;
					switch (InsertStack.front()->Direction)
					{
					case EDIR_MOVE_UP:
						*DirectionY += InsertStack.front()->speed;
						break;
					case EDIR_MOVE_DOWN:
						*DirectionY -= InsertStack.front()->speed;
						break;
					case EDIR_MOVE_LEFT:
						*DirectionX -= InsertStack.front()->speed;
						break;
					case EDIR_MOVE_RIGHT:
						*DirectionX += InsertStack.front()->speed;
						break;
					}
					std::cout << "PUSHED! CurrentLOC: x_" << *DirectionX << " y_" << *DirectionY << std::endl;
				}
				InsertStack.pop();
			}
		}
	}

private:

	std::vector<KeyUnit*> KeyUnits;

	std::queue<KeyUnit*> InsertStack;

	float* MoveKey;
	float* DirectionX;
	float* DirectionY;

	KeyEventBase(float* PTX, float* PTY, float* PTM) : MoveKey(PTM), DirectionX(PTX), DirectionY(PTY) {};
	~KeyEventBase() {};
	KeyEventBase(const KeyEventBase&) {};
	KeyEventBase& operator=(const KeyEventBase&) {};
};