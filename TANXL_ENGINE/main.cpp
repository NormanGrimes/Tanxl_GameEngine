﻿
//████████╗  █████╗   ███╗      ██╗ ██╗    ██╗ ██╗
//╚══██╔══╝██╔══██╗ ████╗    ██║ ╚██╗██╔╝ ██║
//      ██║      ███████║ ██╔██╗  ██║   ╚███╔╝   ██║
//      ██║      ██╔══██║ ██║╚██╗██║   ██╔██╗   ██║
//      ██║      ██║    ██║ ██║  ╚████║ ██╔╝  ██╗ ███████╗
//      ╚═╝      ╚═╝    ╚═╝ ╚═╝    ╚═══╝ ╚═╝    ╚═╝ ╚══════╝


#pragma once

#include "Tanxl_Engine_Manager.h"

int main()
{	
	Tanxl_Engine TGE;
	//检测引擎12状态 是否有异常产生
	TGE.Engine_Check_Engine_Status();
	//构造15x15个区块的(10x10)程序生成世界 并建立数据间的连接
	TGE.Engine_Save_Infinite_State(true, 15, 15);
	//生成引擎数据文件 "Tanxl Engine SystemInfor.sd"
	TGE.Engine_Save_Source_Infor("Tanxl Engine SystemInfor");
	//设置屏幕显示宽度和高度为4个地图单元长度 并设置显示区域外每个方向额外加载4个地图单元长度
	TGE.Engine_State_Set_Display(4, 4, 4);
	//调用引擎接口注册一个事件按钮
	Key_Unit* KU = TGE.Engine_Insert_Regist_Move(GLFW_KEY_E);
	//禁止玩家控制的单元移动到屏幕显示区域以外
	TGE.Engine_Insert_State_Limit(true);
	//启用移动到达指定范围后地图随玩家移动 设置距离为0.6倍某方向距离的长度
	TGE.Engine_Insert_State_MoveWith(true, 0.6f);
	//启动地图视角自动调整 将玩家单元调整到地图中心位置 每次调整距离为0.005并可在移动中调整
	TGE.Engine_Adjust_Multi_Set(true, 0.005f, true);
	//编辑四个区块的内容
	TGE.Engine_State_Set_Data(0, true, false,
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"b-1,b-0,b-1,b-0,a-3,b-2,b-0,b-1,b-0,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,");
	TGE.Engine_State_Set_Data(14, true, false,
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"b-1,b-0,b-1,b-0,b-2,a-3,b-0,b-1,b-0,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,");
	TGE.Engine_State_Set_Data(210, true, false,
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,b-0,b-1,b-0,a-3,b-2,b-0,b-1,b-0,b-1,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,");
	TGE.Engine_State_Set_Data(224, true, false,
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,b-0,b-1,b-0,b-2,a-3,b-0,b-1,b-0,b-1,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,");
	//设置起始区域为第113(从零开始计算)号区块 并覆盖此区块的数据
	TGE.Engine_State_Set_Data(113, true, true,
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,b-0,b-1,b-0,b-2,b-2,b-0,b-1,b-0,b-1,"
		"b-1,a-3,b-1,b-2,b-0,b-0,b-2,b-1,a-3,b-1,"
		"a-3,b-0,b-2,b-1,b-1,b-1,b-1,b-2,b-0,a-3,"
		"b-1,b-2,b-0,a-3,b-0,b-0,a-3,b-0,b-2,b-1,"
		"b-2,b-1,a-3,b-1,b-1,b-1,b-1,a-3,b-1,b-2,");

	while (1)
	{
		static bool Appended{ false };
		static int DropCnt{ 0 };

		DropCnt++;
		if (DropCnt > 5000)
		{
			DropCnt = 0;
			TGE.Engine_Invent_Update_Drop();
		}

		TGE.Engine_Insert_State_Update();//Key Insert

		TGE.Engine_Draw_State_Adjust(0);//Draw Once

		if (KU->Get_KeyStatus())
		{
			if (Appended == false)
			{
				Appended = true;
				TGE.Engine_Insert_Adjust_Speed(0, 8, 0.01);
			}
		}
		else
		{
			if (Appended == true)
			{
				Appended = false;
				TGE.Engine_Insert_Adjust_Speed(0, 8, -0.01);
			}
		}
	}
}
