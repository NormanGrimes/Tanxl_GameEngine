//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-10 09:43
// 为存储模块系统信息提供标准文档
// 为所有switch增加默认的break
// 增加地图块数据的预定义

#pragma once

#ifndef _TANXL_DATADEFINE_
#define _TANXL_DATADEFINE_

#include <string>

const int TANXL_TYPE_MAXIMUM = 1;
const int TANXL_EXAC_MAXIMUM = 0;

const int TANXL_DATA_LENGTH[TANXL_TYPE_MAXIMUM + 1][TANXL_EXAC_MAXIMUM + 1]{ {1}, {2} };

static std::string DataTag(int Type = 0xFF, int Exac = 0xFF, int DAT1 = 0xFF, int DAT2 = 0xFF, int DAT3 = 0xFF)
{
	if ((DAT1 == 0xFF) && (DAT2 == 0xFF) && (DAT3 == 0xFF))
	{
		switch (Type)
		{
		case 0:
			return "VERSION_INFORMATION";
		default:
			break;
		}

		switch (Exac)
		{
		case 0:
			return "ENGINE-CORE";
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
	// |  02  | TANXL_GAMEEVENT       |
	// |  03  | TANXL_GAMESTATE       |
	// |  04  | TANXL_INSERTACTION    |
	// |  05  | TANXL_OPENGL_DRAW     |
	// |  06  | TANXL_ENGINE_MANAGER  |
	// |------|-----------------------|

	if (Type == 0 && Exac == 0)
	{
		switch (DAT1)
		{
		case 0:
			return "TANXL_CONSOLE_LIST";
		case 1:
			return "TANXL_DATABASE";
		case 2:
			return "TANXL_GAMEEVENT";
		case 3:
			return "TANXL_GAMESTATE";
		case 4:
			return "TANXL_INSERTACTION";
		case 5:
			return "TANXL_OPENGL_DRAW";
		case 6:
			return "TANXL_ENGINE_MANAGER";
		default:
			break;
		}
	}

	// |------|-----------------------|
	// | Type |                       |
	// |------|-----------------------|
	// |   1  | GAME_STATE_SAVE       |
	// |------|-----------------------|------|-----------------------|
	// | DAT1 |                       | DAT2 |                       |
	// |------|-----------------------|------|-----------------------|
	// |  00  | CURRENT_UNIQUE_ID     |  00  | GAME_STATE_BLOCK_DATA |
	// |  01  | UNIQUE_ID_LEFT        |------|-----------------------|
	// |  02  | UNIQUE_ID_RIGHT       |
	// |  03  | UNIQUE_ID_ABOVE       |
	// |  04  | UNIQUE_ID_BELOW       |
	// |  05  | UNIQUE_ID_LEFT_ABOVE  |
	// |  06  | UNIQUE_ID_LEFT_BELOW  |
	// |  07  | UNIQUE_ID_RIGHT_ABOVE |
	// |  08  | UNIQUE_ID_RIGHT_BELOW |
	// |------|-----------------------|

	else if (Type == 1)
	{
		switch (DAT1)
		{
		case 0:
			return "CURRENT_UNIQUE_ID";
		case 1:
			return "UNIQUE_ID_LEFT";
		case 2:
			return "UNIQUE_ID_RIGHT";
		case 3:
			return "UNIQUE_ID_ABOVE";
		case 4:
			return "UNIQUE_ID_BELOW";
		case 5:
			return "UNIQUE_ID_LEFT_ABOVE";
		case 6:
			return "UNIQUE_ID_LEFT_BELOW";
		case 7:
			return "UNIQUE_ID_RIGHT_ABOVE";
		case 8:
			return "UNIQUE_ID_RIGHT_BELOW";
		default:
			break;
		}

		switch (DAT2)
		{
		case 0:
			return "GAME_STATE_BLOCK_DATA";
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