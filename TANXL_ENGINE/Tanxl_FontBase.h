//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-10 15:58
// �ӻ���ģ���ж���������ģ��
// ��ȡ����ӿ����ӱ�ż��
// �������������Ĳ�
// ��Ϊ�̳������������
// ������������ö��
// ��������ö�ٲ������ڲ��洢����·��
// ����ͨ��ö�ٳ�ʼ������Ĺ���

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
	�����Ƹɱ���
};

struct Character
{
	GLuint     TextureID;  // ��������ID
	glm::ivec2 Size;       // ���δ�С
	glm::ivec2 Bearing;    // ���λ��ڻ��ߺ�����λ��
	GLuint     Advance;    // ��㵽��һ���������ľ���
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
		"Fonts/������-�ɱ���.ttf"
	};

	std::map<GLchar, Character> _Characters[5];
};

#endif