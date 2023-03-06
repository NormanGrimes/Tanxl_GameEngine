#include "Tanxl_Engine_Manager.h"
#include <iomanip>
int main()
{
	//Data Function Test

	Tanxl_Engine TGE;

	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };
	std::cout << "Generate : " << UIB->Generate() << std::endl;

	TANXL_DataBase NData(true);
	unsigned n = 0x10101010, i = 10;
	while (i--)
	{
		if (i % 10 != 0)
			n++;
		else
			n += 0x01000000;

		if ((n & 0x0f000000) == 0x0f000000)
			n -= 0x0f000000;

		if ((n & 0xf0000000) == 0xf0000000)
			n -= 0xf0000000;

		std::cout << "Updating : " << std::setbase(16) << n << std::endl;
		NData.Set_Instance (n, "Updating" + std::to_string(n));
		std::cout << NData;
		NData.AppendItem(true);
	}
	//NData.Print_Data();

	//Get Instance

	GameStateBase* GSB{&GameStateBase::Get_StateBase(1, 1)};

	TGE.Engine_State_Set_Display(5, 5);

	/*TGE.Engine_State_Compile_Uints(
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,"
		"a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,a-0,a-1,");*/

	TGE.Engine_State_Compile_Uints(10, 10,
		"a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,"
		"a-1,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-1,"
		"a-1,a-0,a-1,a-1,a-1,a-1,a-1,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-0,a-0,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-1,a-1,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-0,a-0,a-0,a-0,a-1,a-0,a-1,"
		"a-1,a-0,a-1,a-1,a-1,a-1,a-1,a-1,a-0,a-1,"
		"a-1,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-0,a-1,"
		"a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,a-1,");

	GSB->Set_Adjust(0.002f);

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	//InsertKey Init

	Key_Unit MOVE_UP;
	MOVE_UP.GLFW_KEY = GLFW_KEY_UP;
	MOVE_UP.MoveLen = 0.01;
	MOVE_UP.MoveToY = true;
	IEB->RegistEvent(MOVE_UP);
	MOVE_UP.GLFW_KEY = GLFW_KEY_W;
	IEB->RegistEvent(MOVE_UP);

	Key_Unit MOVE_LEFT;
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_LEFT;
	MOVE_LEFT.MoveLen = -0.01;
	MOVE_LEFT.MoveToX = true;
	IEB->RegistEvent(MOVE_LEFT);
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_A;
	IEB->RegistEvent(MOVE_LEFT);

	Key_Unit MOVE_RIGHT;
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_RIGHT;
	MOVE_RIGHT.MoveLen = 0.01;
	MOVE_RIGHT.MoveToX = true;
	IEB->RegistEvent(MOVE_RIGHT);
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_D;
	IEB->RegistEvent(MOVE_RIGHT);

	Key_Unit MOVE_DOWN;
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_DOWN;
	MOVE_DOWN.MoveLen = -0.01;
	MOVE_DOWN.MoveToY = true;
	IEB->RegistEvent(MOVE_DOWN);
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_S;
	IEB->RegistEvent(MOVE_DOWN);

	//IEB->Set_MaxFloat(IEB->Get_AutoFloat(GSB->Get_StateHeight()));

	TGE.Engine_Insert_State_Limit(true);

	OpenGL_Draw OGD(800, 800);
	OGD.Set_PreLoad(5);
	OGD.mainLoop(GSB);
}
