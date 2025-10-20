#pragma once

#include "Tanxl_FontBase.h"

FontBase& FontBase::GetFontBase(ECurren_Language Language)
{
	static FontBase* FontsBase{ new FontBase(Language)};
	return *FontsBase;
}

void FontBase::Init_Fonts(std::string Font_Path)
{
	if (_Internal_Font_Counts > 4)
	{
		std::cout << "ERROR::FREETYPE: Out of space for Fonts" << std::endl;
		return;
	}

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, Font_Path.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)
		};
		_Characters[_Internal_Font_Counts].insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	_Internal_Font_Counts++;
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void FontBase::Init_Fonts(EFontSet Font)
{
	this->Init_Fonts(this->_Internal_FontPath[Font]);
}

void FontBase::Set_Language(ECurren_Language Language)
{
	this->_Internal_Language = Language;
}

void FontBase::Confirm_Language()
{
	if (this->_Internal_Language == LANGUAGE_ENGLISH)
	{
		this->Init_Fonts(EFontSet::JosefinSansSemiBoldItalic);
		this->Init_Fonts(EFontSet::JosefinSansBold);
		this->Init_Fonts(EFontSet::NacelleBlack);
		this->_Internal_Font_Counts = 3;
	}
	else if (this->_Internal_Language == LANGUAGE_FRENCH)
	{
		this->Init_Fonts(EFontSet::JosefinSansSemiBoldItalic);
		this->Init_Fonts(EFontSet::JosefinSansBold);
		this->Init_Fonts(EFontSet::NacelleBlack);
		this->_Internal_Font_Counts = 3;
	}
	else if (this->_Internal_Language == LANGUAGE_RUSSIAN)
	{
		this->Init_Fonts(EFontSet::kremlinPremierRegular);
		this->_Internal_Font_Counts = 1;
	}
}

ECurren_Language FontBase::Get_Language()
{
	return this->_Internal_Language;
}

std::map<GLchar, Character> FontBase::Get_Characters(int Id)
{
	if (Id > _Internal_Font_Counts - 1)
		Id = _Internal_Font_Counts - 1;
	return this->_Characters[Id];
}

const std::string FontBase::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

FontBase::FontBase(ECurren_Language Language) :Tanxl_ClassBase("FontBase", "0.1"), _Internal_Language(Language) {}
FontBase::~FontBase() {}
FontBase::FontBase(const FontBase&) :Tanxl_ClassBase("FontBase", "0.1"), _Internal_Language(LANGUAGE_ENGLISH) {}
FontBase& FontBase::operator=(const FontBase&) { return *this; }