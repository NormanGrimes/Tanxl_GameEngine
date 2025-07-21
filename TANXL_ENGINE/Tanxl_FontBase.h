//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-10 15:58
// 从绘制模块中独立出字体模块
// 获取字体接口增加编号检查
// 整理进入引擎核心层
// 改为继承自引擎基础类
// 增加语言设置枚举
// 增加字体枚举并在类内部存储字体路径
// 增加通过枚举初始化字体的功能

#pragma once

#ifndef _TANXL_FONT_BASE_
#define _TANXL_FONT_BASE_

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_EngineBase.h"

enum ECurren_Language
{
	LANGUAGE_ENGLISH,
	LANGUAGE_CHINESE,
	LANGUAGE_FRENCH,
	LANGUAGE_RUSSIAN,
	LANGUAGE_JAPANESE
};

enum EFontSet
{
	JosefinSansSemiBoldItalic,
	JosefinSansBold,
	NacelleBlack,
	光良酒干杯体
};

struct Character
{
	GLuint     TextureID;  // 字形纹理ID
	glm::ivec2 Size;       // 字形大小
	glm::ivec2 Bearing;    // 字形基于基线和起点的位置
	GLuint     Advance;    // 起点到下一个字形起点的距离
};

class FontBase : public Tanxl_ClassBase
{
public:
	static FontBase& GetFontBase();

	void Init_Fonts(std::string Font_Path);

	void Init_Fonts(EFontSet Font);

	std::map<GLchar, Character> Get_Characters(int Id);

	const std::string Get_Version();

private:

	FontBase();
	~FontBase();
	FontBase(const FontBase&);
	FontBase& operator=(const FontBase&);

	int _Internal_Font_Counts{ 0 };

	std::string _Internal_FontPath[4]
	{
		"Fonts/JosefinSans-SemiBoldItalic.ttf",
		"Fonts/JosefinSans-Bold.ttf",
		"Fonts/Nacelle-Black.otf",
		"Fonts/光良酒-干杯体.ttf"
	};

	std::map<GLchar, Character> _Characters[5];
};

#endif