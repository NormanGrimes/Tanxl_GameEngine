//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-10 15:58
// �ӻ���ģ���ж���������ģ��
// ��ȡ����ӿ����ӱ�ż��
// �������������Ĳ�
// ��Ϊ�̳������������
// ������������ö��
// ��������ö�ٲ������ڲ��洢����·��
// ����ͨ��ö�ٳ�ʼ������Ĺ���
// �������Եĳ�ʼ�����������ýӿ�
// ����ȷ�����Խӿ�����ͳһ��ʼ��
// ����һ����������
// �����ʼ���ӿ�������Ľ����޸�

#pragma once

#ifndef _TANXL_FONT_BASE_
#define _TANXL_FONT_BASE_

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_EngineBase.h"

enum EFontSet
{
	JosefinSansSemiBoldItalic,
	JosefinSansBold,
	NacelleBlack,
	GuangLiangFont,
	kremlinPremierRegular
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
	static FontBase& GetFontBase(ECurren_Language Language = LANGUAGE_ENGLISH);

	void Init_Fonts(std::string Font_Path);

	void Init_Fonts(EFontSet Font);

	void Set_Language(ECurren_Language Language);

	void Confirm_Language();

	ECurren_Language Get_Language();

	std::map<GLchar, Character> Get_Characters(int Id);

	const std::string Get_Version();

private:

	FontBase(ECurren_Language Language);
	~FontBase();
	FontBase(const FontBase&);
	FontBase& operator=(const FontBase&);

	int _Internal_Font_Counts{ 0 };

	std::string _Internal_FontPath[5]
	{
		"Fonts/JosefinSans-SemiBoldItalic.ttf",
		"Fonts/JosefinSans-Bold.ttf",
		"Fonts/Nacelle-Black.otf",
		"Fonts/GuangLiang.ttf",
		"Fonts/kremlin-premier.regular.ttf"
	};

	std::map<GLchar, Character> _Characters[5];

	ECurren_Language _Internal_Language;
};

#endif