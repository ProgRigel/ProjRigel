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

	void RgGUIGlyph::GenFontImage()
	{
		m_pimg = RgImage::Craete(256, 256, RgImageFormat::R8G8B8A8);

		m_pfont->SetPixelSize(32);
		m_pfont->LoadGlyph('R');
		m_pfont->RenderToImage(m_pimg, 0, 0);
	}

}
