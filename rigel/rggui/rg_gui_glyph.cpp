#include "rggui.h"
#include "rg_gui_glyph.h"
#include <rgcore\rgcore.h>
#include <rgcore\rg_image.h>
namespace rg {
	RgGUIGlyph::RgGUIGlyph(std::wstring fontpath)
	{
	}

	RgGUIGlyph::RgGUIGlyph()
	{
		RgLogD() << "init gui glyph";
		auto ttfpath = GetWorkDirectory() + L"/Data/Res/droid_sans_mono.ttf";

		auto font = RgFontManager::LoadFont(tostring(ttfpath));
		if (font == nullptr || font->IsValid() == false) {
			m_bIsValid = false;
			RgFontManager::UnloadFont(font);
			font = nullptr;
		}
		m_pfont = font;
		m_bIsValid = true;
		GenFontImage();
		GenCharUV();

		RgLogD() << "#" << m_charrect['#'].toStr() << m_charuv['#' * 4].toStr();

	}

	RgGUIGlyph::~RgGUIGlyph()
	{
		Release();
	}
	void RgGUIGlyph::Release()
	{
		if (m_pimg != nullptr) {
			delete m_pimg;
			m_pimg = nullptr;
		}

		if (m_pfont != nullptr) {
			RgFontManager::UnloadFont(m_pfont);
			m_pfont = nullptr;
		}
	}

	bool RgGUIGlyph::IsValid() const
	{
		return m_bIsValid;
	}

	RgImage * RgGUIGlyph::GetImage()
	{
		return m_pimg;
	}

	void RgGUIGlyph::SetCharUV(const char c, RgVec2 & uv, unsigned int vi) const
	{
		auto& crect = m_charrect[c];

		float ax = crect.x / 256.0f;
		float ay = crect.y / 256.0f;
		float bx = (crect.x + crect.z) / 256.0f;
		float by = (crect.y + crect.w) / 256.0f;
		if (vi == 0) {
			uv.x = ax;
			uv.y = ay;
		}
		else if (vi == 1) {
			uv.x = bx;
			uv.y = ay;
		}
		else if (vi == 2) {
			uv.x = bx;
			uv.y = by;
		}
		else
		{
			uv.x = ax;
			uv.y = by;
		}
	}

	const RgVec2& RgGUIGlyph::GetCharUV(const char c, unsigned int vi) const
	{
		return m_charuv[c * 4 + vi];
	}

	void RgGUIGlyph::GenFontImage()
	{
		m_pimg = RgImage::Craete(256, 256, RgImageFormat::R8G8B8A8);


		unsigned int linewidth = 0;
		unsigned int lineheight = 0;

		unsigned int linemaxh = 0;
		m_pfont->SetPixelSize(14);

		for (unsigned int i = 32; i < 128; i++) {
			m_pfont->LoadGlyph(i);
			auto w = m_pfont->m_glyph.bitmapWidth;
			auto h = m_pfont->m_glyph.bitmapHeight;
			auto x = m_pfont->m_glyph.bitmapLeft;
			auto y = m_pfont->m_glyph.bitmapTop;

			w = 16;
			h = 16;
			if (linewidth + w > 255) {
				lineheight += linemaxh;
				m_pfont->RenderToImage(m_pimg, 0, lineheight);
				m_charrect[i] = RgVec4(0, lineheight, w, h);
				linewidth = w;
				linemaxh = h;
			}
			else
			{
				m_pfont->RenderToImage(m_pimg, linewidth, lineheight);
				m_charrect[i] = RgVec4((int)linewidth, lineheight, w, h);
				linewidth += w;
				linemaxh = h > linemaxh ? h : linemaxh;
			}
			//linewidth += 2;
			
		}
	}

	void RgGUIGlyph::GenCharUV()
	{
		for (unsigned int i = 32; i < 128; i++) {
			auto& r = m_charrect[i] / 256.0f;
			m_charuv[i * 4] = RgVec2(r.x, r.y);
			m_charuv[i * 4 + 1] = RgVec2(r.x + r.z, r.y);
			m_charuv[i * 4 + 2] = RgVec2(r.x + r.z, r.y + r.w);
			m_charuv[i * 4 + 3] = RgVec2(r.x, r.y + r.w);

			//RgLogD() << m_charuv[i*4].toStr();
		}
	}

}
