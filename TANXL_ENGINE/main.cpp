﻿
//████████╗  █████╗   ███╗      ██╗ ██╗    ██╗ ██╗
//╚══██╔══╝██╔══██╗ ████╗    ██║ ╚██╗██╔╝ ██║
//      ██║      ███████║ ██╔██╗  ██║   ╚███╔╝   ██║
//      ██║      ██╔══██║ ██║╚██╗██║   ██╔██╗   ██║
//      ██║      ██║    ██║ ██║  ╚████║ ██╔╝  ██╗ ███████╗
//      ╚═╝      ╚═╝    ╚═╝ ╚═╝    ╚═══╝ ╚═╝    ╚═╝ ╚══════╝


#pragma once

#include "Tanxl_Engine_Manager.h"

#include "Tanxl_GameTips.h"

int main()
{
	Tanxl_Engine TGE;
	//检测引擎12状态 是否有异常产生
	TGE.Engine_Check_Engine_Status();
	//构造31x31个区块的(10x10)程序生成世界 并建立数据间的连接
	TGE.Engine_Save_Infinite_State(true, 5, 5, 80, 80);
	//生成引擎数据文件 "Tanxl Engine SystemInfor.sd"
	TGE.Engine_Save_Source_Infor("Tanxl Engine SystemInfor");
	//设置屏幕显示宽度和高度为4个地图单元长度 并设置显示区域外每个方向额外加载4个地图单元长度
	TGE.Engine_State_Set_Display(6, 6, 3);
	//调用引擎接口注册一个事件按钮
	Key_Unit* KU = TGE.Engine_Insert_Regist_Move(GLFW_KEY_E);
	//禁止玩家控制的单元移动到屏幕显示区域以外
	TGE.Engine_Insert_State_Limit(true);
	//启用移动到达指定范围后地图随玩家移动 设置距离为0.6倍某方向距离的长度
	TGE.Engine_Insert_State_MoveWith(true, 0.6f);
	//启动地图视角自动调整 将玩家单元调整到地图中心位置 每次调整距离为0.005并可在移动中调整
	TGE.Engine_Adjust_Multi_Set(true, 0.19f, true);
	//编辑四个区块的内容
	TGE.Engine_State_Set_Data(0x5151, false,
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"0-2,0-1,0-2,0-1,1-4,0-3,0-1,0-2,0-1,0-2,"
		"0-2,0-1,0-2,0-1,0-3,0-3,0-1,0-2,0-1,0-2,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,");
	TGE.Engine_State_Set_Data(0x5153, false,
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"0-2,0-1,0-2,0-1,0-3,1-4,0-1,0-2,0-1,0-2,"
		"0-2,0-1,0-2,0-1,0-3,0-3,0-1,0-2,0-1,0-2,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,");
	TGE.Engine_State_Set_Data(0x5351, false,
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"0-2,0-1,0-2,0-1,0-3,0-3,0-1,0-2,0-1,0-2,"
		"0-2,0-1,0-2,0-1,1-4,0-3,0-1,0-2,0-1,0-2,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,");
	TGE.Engine_State_Set_Data(0x5353, false,
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"0-2,0-1,0-2,0-1,0-3,0-3,0-1,0-2,0-1,0-2,"
		"0-2,0-1,0-2,0-1,0-3,1-4,0-1,0-2,0-1,0-2,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,");
	//设置起始区域为第480(从零开始计算)号区块 并覆盖此区块的数据
	TGE.Engine_State_Set_Data(0x5252, true,
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"0-2,0-1,0-2,0-1,0-3,0-3,0-1,0-2,0-1,0-2,"
		"0-2,0-1,0-2,0-1,0-3,0-3,0-1,0-2,0-1,0-2,"
		"0-2,1-4,0-2,0-3,0-1,0-1,0-3,0-2,1-4,0-2,"
		"1-4,0-1,0-3,0-2,0-2,0-2,0-2,0-3,0-1,1-4,"
		"0-2,0-3,0-1,1-4,0-1,0-1,1-4,0-1,0-3,0-2,"
		"0-3,0-2,1-4,0-2,0-2,0-2,0-2,1-4,0-2,0-3,");

	while (1)
	{
		static bool Appended{ false };
		static int DropCnt{ 0 };

		DropCnt++;
		if (DropCnt > 5)
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
				TGE.Engine_Insert_Adjust_Speed(0, 8, 0.5);
			}
		}
		else
		{
			if (Appended == true)
			{
				Appended = false;
				TGE.Engine_Insert_Adjust_Speed(0, 8, -0.5);
			}
		}
	}
}
