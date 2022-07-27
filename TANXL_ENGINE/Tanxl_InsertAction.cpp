#include "Tanxl_InsertAction.h"

Key_Unit::Key_Unit() :GLFW_KEY(NULL), MoveToX(false), MoveToY(false), MoveLen(0.0f) {}

Key_Unit::Key_Unit(int GLKEY, bool MOVX, bool MOVY, float MOVL)
	: GLFW_KEY(GLKEY), MoveToX(MOVX), MoveToY(MOVY), MoveLen(MOVL) {}

InsertEventBase& InsertEventBase::GetInsertBase()
{
	static InsertEventBase* IEB = new InsertEventBase;
	return *IEB;
}

void InsertEventBase::RegistEvent(Key_Unit KU)
{
	KeyEventS.push_back(KU);
}

void InsertEventBase::GetInsert(GLFWwindow* window, float* MoveX, float* MoveY)
{
	for (int i = 0; i < KeyEventS.size(); i++)
	{
		if (glfwGetKey(window, KeyEventS.at(i).GLFW_KEY) == GLFW_PRESS)
		{
			if (KeyEventS.at(i).MoveToX)
				*MoveX += KeyEventS.at(i).MoveLen;
			if (KeyEventS.at(i).MoveToY)
				*MoveY += KeyEventS.at(i).MoveLen;
			AutoCheck(MoveX, MoveY);
			std::cout << "BUTTON PUSHED x_" << *MoveX << "y_" << *MoveY << std::endl;
		}
	}
}

void InsertEventBase::Set_MaxFloat(float Max_float)
{
	this->_Max_float = Max_float;
}

void InsertEventBase::AutoCheck(float* MoveX, float* MoveY)
{
	if (*MoveX >= _Max_float)
		*MoveX = _Max_float;
	else if (*MoveX <= -_Max_float)
		*MoveX = -_Max_float;

	if (*MoveY >= _Max_float)
		*MoveY = _Max_float;
	else if (*MoveY <= -_Max_float)
		*MoveY = -_Max_float;
}

//UnImportant µ¥ÀýÊµÏÖ

InsertEventBase::InsertEventBase() :KeyEventS(NULL), _Max_float(1.0f) {}

InsertEventBase::~InsertEventBase()
{
	for (int i = 0; i < KeyEventS.size(); i++)
		delete &KeyEventS.at(i);
	KeyEventS.clear();
}

InsertEventBase::InsertEventBase(const InsertEventBase&) :KeyEventS(NULL), _Max_float(1.0f) {}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}