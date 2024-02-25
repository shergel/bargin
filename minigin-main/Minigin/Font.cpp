#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* bgn::Font::GetFont() const {
	return m_font;
}

bgn::Font::Font(const std::string& fullPath, unsigned int size) : m_font(nullptr)
{
	m_font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

bgn::Font::~Font()
{
	TTF_CloseFont(m_font);
}
