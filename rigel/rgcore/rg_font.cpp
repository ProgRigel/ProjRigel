#include "rgcore.h"
#include "rg_font.h"
#include "rg_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace rg {

	//////////////////////////////////
	//RgFontManager

	static FT_Library s_ftlibrary;
	static bool s_ftinited = false;
	std::vector<RgFont*> RgFontManager::s_vFonts;

	RgFontManager::RgFontManager()
	{
	}
	RgFontManager::~RgFontManager()
	{
	}

	RgFont* RgFontManager::LoadFont(const std::string ttfpath)
	{
		if (!CheckFTInited()) return nullptr;

		FT_Face face;
		auto error = FT_New_Face(s_ftlibrary, ttfpath.c_str(), 0, &face);
		if (error) {
			if(face != nullptr)
				FT_Done_Face(face);
			RgLogE() << "create ft face error";
			return nullptr;
		}

		RgFont* font = new RgFont();
		font->m_pftface = face;
		s_vFonts.push_back(font);

		return font;
	}

	void RgFontManager::UnloadFont(RgFont * font)
	{
		RG_ASSERT(font != nullptr);
		font->Release();
	}

	void RgFontManager::Release()
	{
		for (auto face : s_vFonts) {
			if (face != nullptr) {
				face->Release();
				delete face;
				face = nullptr;
			}
			
		}
		std::vector<RgFont*>().swap(s_vFonts);

		FT_Done_FreeType(s_ftlibrary);
	}

	bool RgFontManager::CheckFTInited()
	{
		if (s_ftinited) return true;
		auto error = FT_Init_FreeType(&s_ftlibrary);
		if (error) {
			RgLogE() << "init freetype error";
			return false;
		}
		s_ftinited = true;
		return true;
	}

	//////////////////////////////////
	//RgFont

	RgFont::RgFont()
	{
	}

	RgFont::~RgFont()
	{
	}

	bool RgFont::IsValid() const
	{
		return m_valid;
	}

	void RgFont::SetPixelSize(const unsigned int size)
	{
		auto error = FT_Set_Pixel_Sizes((FT_Face)m_pftface, size, size);
		if (error) {
			RgLogE() << "freetype set pixel size error:" << error;
			return;
		}
		m_pixelsize = size;
		m_layoutAscender = ((FT_Face)m_pftface)->size->metrics.ascender >> 6;
	}

	void RgFont::LoadGlyph(unsigned long c)
	{
		auto error = FT_Load_Char((FT_Face)m_pftface, c, FT_LOAD_RENDER);
		if (error) {
			RgLogE() << "ft load char error" << error;
			return;
		}

		FT_GlyphSlot slot = ((FT_Face)m_pftface)->glyph;
		m_glyph.bitmapWidth = slot->bitmap.width;
		m_glyph.bitmapHeight = slot->bitmap.rows;
		m_glyph.bitmapTop = slot->bitmap_top;
		m_glyph.bitmapLeft = slot->bitmap_left;
		m_glyph.advance = ((slot->advance.x) >> 6);
	}

	void RgFont::RenderToImage(const RgImage * img, const unsigned int posx, const unsigned int posy) const
	{

	}

	void RgFont::RenderText(std::string text, const RgImage * img, const unsigned int posx, const unsigned int posy)
	{
	}

	void RgFont::Release()
	{
		m_valid = false;
		if (m_pftface != nullptr) {
			FT_Face face = (FT_Face)m_pftface;
			if (face != nullptr) {
				FT_Done_Face(face);
				m_pftface = nullptr;
			}
		}
	}

	//////////////////////////////////
}
