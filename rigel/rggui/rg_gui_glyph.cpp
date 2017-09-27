#include "rggui.h"
#include "rg_gui_glyph.h"
#include <rgcore\rg_font.h>
#include <rgcore\rgcore.h>
namespace rg {
	RgGUIGlyph::RgGUIGlyph(std::wstring fontpath)
	{
	}

	RgGUIGlyph::RgGUIGlyph()
	{
		RgLogD() << "init gui glyph";
		auto ttfpath = GetWorkDirectory() + L"/Data/Res/droid_sans_mono.ttf";

		auto font = RgFontManager::LoadFont(tostring(ttfpath));
	}

	RgGUIGlyph::~RgGUIGlyph()
	{
		Release();
	}

	void RgGUIGlyph::Release()
	{
		if (m_pfont != nullptr) {
			RgFontManager::UnloadFont(m_pfont);
			m_pfont = nullptr;
		}
	}

	bool RgGUIGlyph::IsValid() const
	{
		return m_bIsValid;
	}

}
