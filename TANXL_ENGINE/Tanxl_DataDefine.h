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
// 存储模块编号关键字改为与其他编号统一

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
	// |  09  | TANXL_SOUNDBASE       |
	// |  10  | TANXL_FONTBASE        |
	// |  11  | TANXL_ENGINE_MANAGER  |
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
			return "TANXL_SOUNDBASE";
		case 10:
			return "TANXL_FONTBASE";
		case 11:
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
	// |  00  | UNIQUE_ID_CURRENT	  |
	// |  01  | GAME_STATE_BLOCK_DATA |	
	// |  02  | UNIQUE_ID_LEFT        |
	// |  03  | UNIQUE_ID_RIGHT       |
	// |  04  | UNIQUE_ID_ABOVE       |
	// |  05  | UNIQUE_ID_BELOW       |
	// |  06  | UNIQUE_ID_LEFT_ABOVE  |
	// |  07  | UNIQUE_ID_LEFT_BELOW  |
	// |  08  | UNIQUE_ID_RIGHT_ABOVE |
	// |  09  | UNIQUE_ID_RIGHT_BELOW |
	// |------|-----------------------|

	else if (Type == 1)
	{
		switch (Data)
		{
		case 0:
			return "UNIQ_CURRENT";
		case 1:
			return "UNIQ_BLOCK_DATA";
		case 2:
			return "UNIQ_LEFT";
		case 3:
			return "UNIQ_RIGHT";
		case 4:
			return "UNIQ_ABOVE";
		case 5:
			return "UNIQ_BELOW";
		case 6:
			return "UNIQ_LABOVE";
		case 7:
			return "UNIQ_LBELOW";
		case 8:
			return "UNIQ_RABOVE";
		case 9:
			return "UNIQ_RBELOW";
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