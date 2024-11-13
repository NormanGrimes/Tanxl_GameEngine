//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-10 09:43
// 为存储模块系统信息提供标准文档
// 为所有switch增加默认的break
// 增加地图块数据的预定义
// 增加更多预定义数据
// 修改数据标签接口对应存储模块改动
// 增加坐标模块的支持
// 移除未使用变量并调整数据顺序
// 适配存储模块的改动

#pragma once

#ifndef _TANXL_DATADEFINE_
#define _TANXL_DATADEFINE_

#include <string>

static std::string DataTag(int Type = 0xFFFF, int Exac = 0xFFFF, int Data = 0xFFFF)
{
	if (Data == 0xFFFF)
	{
		switch (Type)
		{
		case 0:
			return "VERSION_INFORMATION";
		case 1:
			return "GAME_STATE_SAVE";
		case 2:
			return "DATA_CHAIN_SPACE";
		default:
			break;
		}

		switch (Exac)
		{
		case 0:
			return "ENGINE_CORE";
		default:
			break;
		}
	}
	// |------|-----------------------|------|-----------------------|
	// | Type |                       | Exac |                       |
	// |------|-----------------------|------|-----------------------|
	// |   0  | VERSION_INFORMATION   |   0  | ENGINE-CORE           |
	// |------|-----------------------|------|-----------------------|
	// | DAT1 |                       |
	// |------|-----------------------|
	// |  00  | TANXL_CONSOLE_LIST    |
	// |  01  | TANXL_DATABASE        |
	// |  02  | TANXL_GAME_EVENT      |
	// |  03  | TANXL_GAME_STATE      |
	// |  04  | TANXL_INSERTACTION    |
	// |  05  | TANXL_OPENGL_DRAW     |
	// |  06  | TANXL_RANDOMBASE      |
	// |  07  | TANXL_LOCATIONBASE    |
	// |  08  | TANXL_GAME_OBJECTBASE |
	// |  09  | TANXL_ENGINE_MANAGER  |
	// |------|-----------------------|

	if ((Type == 0) && (Exac == 0))
	{
		switch (Data)
		{
		case 0:
			return "TANXL_CONSOLE_LIST";
		case 1:
			return "TANXL_DATABASE";
		case 2:
			return "TANXL_GAME_EVENT";
		case 3:
			return "TANXL_GAME_STATE";
		case 4:
			return "TANXL_INSERTACTION";
		case 5:
			return "TANXL_OPENGL_DRAW";
		case 6:
			return "TANXL_RANDOMBASE";
		case 7:
			return "TANXL_LOCATIONBASE";
		case 8:
			return "TANXL_GAME_OBJECTBASE";
		case 9:
			return "TANXL_ENGINE_MANAGER";
		default:
			break;
		}
	}

	// |------|-----------------------|
	// | Type |                       |
	// |------|-----------------------|
	// |   1  | GAME_STATE_SAVE       |
	// |------|-----------------------|
	// | DAT1 |                       |
	// |------|-----------------------|
	// |  00  | CURRENT_UNIQUE_ID     |
	// |  01  | UNIQUE_ID_LEFT        |
	// |  02  | UNIQUE_ID_RIGHT       |
	// |  03  | UNIQUE_ID_ABOVE       |
	// |  04  | UNIQUE_ID_BELOW       |
	// |  05  | UNIQUE_ID_LEFT_ABOVE  |
	// |  06  | UNIQUE_ID_LEFT_BELOW  |
	// |  07  | UNIQUE_ID_RIGHT_ABOVE |
	// |  08  | UNIQUE_ID_RIGHT_BELOW |
	// |  09  | GAME_STATE_BLOCK_DATA |
	// |------|-----------------------|

	else if (Type == 1)
	{
		switch (Data)
		{
		case 0:
			return "CURRENT_UNIQUE_ID";
		case 1:
			return "GAME_STATE_BLOCK_DATA";
		case 2:
			return "UNIQUE_ID_LEFT";
		case 3:
			return "UNIQUE_ID_RIGHT";
		case 4:
			return "UNIQUE_ID_ABOVE";
		case 5:
			return "UNIQUE_ID_BELOW";
		case 6:
			return "UNIQUE_ID_LEFT_ABOVE";
		case 7:
			return "UNIQUE_ID_LEFT_BELOW";
		case 8:
			return "UNIQUE_ID_RIGHT_ABOVE";
		case 9:
			return "UNIQUE_ID_RIGHT_BELOW";
		default:
			break;
		}
	}


	// |------|-----------------------|------|-----------------------|
	// | Type |                       | Exac |                       |
	// |------|-----------------------|------|-----------------------|
	// |      | //////////////////    |      | //////////////////    |
	// |------|-----------------------|------|-----------------------|------|-----------------------|
	// | DAT1 |                       | DAT2 |                       | DAT3 |                       |
	// |------|-----------------------|------|-----------------------|------|-----------------------|
	// |  00  | //////////////////    |      |                       |      |                       |
	// |  01  | //////////////////    |      |                       |      |                       |
	// |  02  | //////////////////    |      |                       |      |                       |
	// |  03  | //////////////////    |      |                       |      |                       |
	// |  04  | //////////////////    |      |                       |      |                       |
	// |  05  | //////////////////    |      |                       |      |                       |
	// |------|-----------------------|------|-----------------------|------|-----------------------|
	//throw "UNKNOWN DATA PLEASE CHECK DATATAG() FOR MORE INFORMATION";
	return "";
}

#endif