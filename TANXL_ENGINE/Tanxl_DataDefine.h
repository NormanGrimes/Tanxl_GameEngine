//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-01-10 09:43
// 为存储模块系统信息提供标准文档

#pragma once

#ifndef _TANXL_DATADEFINE_
#define _TANXL_DATADEFINE_

#include <string>

const int TANXL_TYPE_MAXIMUM = 0;
const int TANXL_EXAC_MAXIMUM = 0;

const int TANXL_DATATAG_OTH1[TANXL_TYPE_MAXIMUM + 1][TANXL_EXAC_MAXIMUM + 1]{ {6} };
const int TANXL_DATATAG_OTH2[TANXL_TYPE_MAXIMUM + 1][TANXL_EXAC_MAXIMUM + 1]{ {0} };
const int TANXL_DATATAG_OTH3[TANXL_TYPE_MAXIMUM + 1][TANXL_EXAC_MAXIMUM + 1]{ {0} };

static std::string DataTag(int Type = 0xFF, int Exac = 0xFF, int OTH1 = 0xFF, int OTH2 = 0xFF, int OTH3 = 0xFF)
{
	if ((OTH1 == 0xFF) && (OTH2 == 0xFF) && (OTH3 == 0xFF))
	{
		switch (Type)
		{
		case 0xFF:
			break;
		case 0:
			return "VERSION_INFORMATION";
		}

		switch (Exac)
		{
		case 0xFF:
			break;
		case 0:
			return "ENGINE-CORE";
		}
	}
	// -----|-----------------------|------|-----------------------|
	// Type |                       | Exac |                       |
	// -----|-----------------------|------|-----------------------|
	//   0  | VERSION_INFORMATION   |   0  | ENGINE-CORE           |
	// -----|-----------------------|------|-----------------------|
	// OTH1 |                       |
	// -----|-----------------------|
	//  00  | TANXL_CONSOLE_LIST    |
	//  01  | TANXL_DATABASE        |
	//  02  | TANXL_GAMEEVENT       |
	//  03  | TANXL_GAMESTATE       |
	//  04  | TANXL_INSERTACTION    |
	//  05  | TANXL_OPENGL_DRAW     |
	// -----|-----------------------|

	if (Type == 0 && Exac == 0)
	{
		switch (OTH1)
		{
		case 00:
			return "TANXL_CONSOLE_LIST";
		case 01:
			return "TANXL_DATABASE";
		case 02:
			return "TANXL_GAMEEVENT";
		case 03:
			return "TANXL_GAMESTATE";
		case 04:
			return "TANXL_INSERTACTION";
		case 05:
			return "TANXL_OPENGL_DRAW";
		}
	}

	// -----|-----------------------|------|-----------------------|
	// Type |                       | Exac |                       |
	// -----|-----------------------|------|-----------------------|
	//   0  | //////////////////    |   0  | //////////////////    |
	// -----|-----------------------|------|-----------------------|------|-----------------------|
	// OTH1 |                       | OTH2 |                       | OTH2 |                       |
	// -----|-----------------------|------|-----------------------|------|-----------------------|
	//  00  | //////////////////    |      |                       |      |                       |
	//  01  | //////////////////    |      |                       |      |                       |
	//  02  | //////////////////    |      |                       |      |                       |
	//  03  | //////////////////    |      |                       |      |                       |
	//  04  | //////////////////    |      |                       |      |                       |
	//  05  | //////////////////    |      |                       |      |                       |
	// -----|-----------------------|------|-----------------------|------|-----------------------|
	//throw "UNKNOWN DATA PLEASE CHECK DATATAG() FOR MORE INFORMATION";
	return "";
}

#endif
