#pragma once
#include <string>
#include <rgcore\rg_image.h>
#include <rgcore\rg_font.h>
namespace rg {

	class RgGUIGlyph {
	public:
		RgGUIGlyph(std::wstring fontpath);
		RgGUIGlyph();
		~RgGUIGlyph();
		void Release();
		bool IsValid() const;

		RgImage* GetImage();

	private:
		RgGUIGlyph(const RgGUIGlyph&) = delete;
		RgGUIGlyph& operator=(const RgGUIGlyph&) = delete;

		void GenFontImage();

		bool m_bIsValid = false;
		RgFont * m_pfont = nullptr;
		RgImage * m_pimg = nullptr;
	};
}