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
	GLuint FontCnts{ 256 };

	for (GLuint c = 0; c < FontCnts; c++)
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
		Character character{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)
		};
		_Characters[_Internal_Font_Counts].insert(std::pair<GLuint, Character>(c, character));
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
	else if (this->_Internal_Language == LANGUAGE_CHINESE)
	{
		this->Init_Fonts(EFontSet::GuangLiangFont);
		this->_Internal_Font_Counts = 1;
	}
}

void FontBase::Bind_FontVAO(GLuint Font_VAO, GLuint Font_VBO)
{
	this->_Font_VAO = Font_VAO;
	this->_Font_VBO = Font_VBO;
}

void FontBase::Set_FontColor(glm::vec3 color)
{
	this->_Font_Color = color;
}

void FontBase::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, int Font_Id)
{
	glUniform3f(0, this->_Font_Color.x, this->_Font_Color.y, this->_Font_Color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->_Font_VAO);

	// Iterate through all characters
	std::wstring wText{ std::wstring(text.begin(),text.end()) };
	for (std::wstring::const_iterator c{ wText.begin() }; c != wText.end(); ++c)
	{
		Character ch{ (this->Get_Characters(Font_Id))[*c] };// Characters[*c];

		GLfloat xpos{ x + ch.Bearing.x * scale };
		GLfloat ypos{ y - (ch.Size.y - ch.Bearing.y) * scale };

		GLfloat w{ ch.Size.x * scale };
		GLfloat h{ ch.Size.y * scale };
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, this->_Font_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

ECurren_Language FontBase::Get_Language() const
{
	return this->_Internal_Language;
}

std::map<wchar_t, Character> FontBase::Get_Characters(int Id)
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