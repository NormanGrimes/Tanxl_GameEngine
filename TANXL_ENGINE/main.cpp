#include "Tanxl_OpenGL_Draw.h"
#include "Tanxl_UniqueID.h"
#include "Tanxl_DataBase.h"
#include <iomanip>
int main()
{
	//Data Function Test

	TANXL_DataBase NData(true);
	int n = 0x10101010, i = 5;
	while (i--)
	{
		std::cout << "Updating : " << std::setbase(16) << n << std::endl;
		NData.Set_Instance(n++, "Updating" + std::to_string(n));
		std::cout << NData;
		NData.AppendItem(false);
	}
	NData.Print_Data();

	//Get Instance

	GameStateBase* GSB{&GameStateBase::Get_StateBase(5, 5)};

	/*GSB->CompileStateUnits("a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
						   "a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		                   "a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
						   "a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
						   "a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
						   "a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
						   "a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,");TEST_STATE_1*/

	GSB->CompileStateUnits("a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,"
						   "a-1,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-1,"
						   "a-1,a-0,a-1,a-1,a-1,a-1,a-1,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-0,a-0,a-0,a-0,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-0,a-1,a-1,a-0,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-0,a-1,a-1,a-0,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-0,a-0,a-0,a-0,a-1,a-0,a-1,"
						   "a-1,a-0,a-1,a-1,a-1,a-1,a-1,a-1,a-0,a-1,"
						   "a-1,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-1,"
						   "a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,");

	GSB->Set_DataAll_State(10, 10);

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	//InsertKey Init

	Key_Unit MOVE_UP;
	MOVE_UP.GLFW_KEY = GLFW_KEY_UP;
	MOVE_UP.MoveLen = 0.01f;
	MOVE_UP.MoveToY = true;
	IEB->RegistEvent(MOVE_UP);
	MOVE_UP.GLFW_KEY = GLFW_KEY_W;
	IEB->RegistEvent(MOVE_UP);

	Key_Unit MOVE_LEFT;
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_LEFT;
	MOVE_LEFT.MoveLen = -0.01f;
	MOVE_LEFT.MoveToX = true;
	IEB->RegistEvent(MOVE_LEFT);
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_A;
	IEB->RegistEvent(MOVE_LEFT);

	Key_Unit MOVE_RIGHT;
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_RIGHT;
	MOVE_RIGHT.MoveLen = 0.01f;
	MOVE_RIGHT.MoveToX = true;
	IEB->RegistEvent(MOVE_RIGHT);
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_D;
	IEB->RegistEvent(MOVE_RIGHT);

	Key_Unit MOVE_DOWN;
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_DOWN;
	MOVE_DOWN.MoveLen = -0.01f;
	MOVE_DOWN.MoveToY = true;
	IEB->RegistEvent(MOVE_DOWN);
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_S;
	IEB->RegistEvent(MOVE_DOWN);

	//IEB->Set_MaxFloat(IEB->Get_AutoFloat(GSB->Get_StateHeight()));

	IEB->Set_MaxFloat_Height(IEB->Get_AutoFloat(GSB->Get_StateHeight() - 2));
	IEB->Set_MaxFloat_Width(IEB->Get_AutoFloat(GSB->Get_StateWidth() - 2));

	IEB->Set_StateRange(true);

	OpenGL_Draw OGD(800, 800);
	OGD.Set_PreLoad(4);
	OGD.mainLoop(GSB);
}
