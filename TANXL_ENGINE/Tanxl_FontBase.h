//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-10-10 15:58
// �ӻ���ģ���ж���������ģ��
// ��ȡ����ӿ����ӱ�ż��
// �������������Ĳ�
// ��Ϊ�̳������������

#pragma once

#ifndef _TANXL_FONT_BASE_
#define _TANXL_FONT_BASE_

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_EngineBase.h"

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

	std::map<GLchar, Character> Get_Characters(int Id);

	const std::string Get_Version();

private:

	FontBase();
	~FontBase();
	FontBase(const FontBase&);
	FontBase& operator=(const FontBase&);

	int _Internal_Font_Counts{ 0 };

	std::map<GLchar, Character> _Characters[5];
};

#endif