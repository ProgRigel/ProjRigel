#pragma once
#include <string>
namespace rg {
	class RgFont;

	class RgGUIGlyph {
	public:
		RgGUIGlyph(std::wstring fontpath);
		RgGUIGlyph();
		~RgGUIGlyph();
		void Release();
		bool IsValid() const;

	private:
		RgGUIGlyph(const RgGUIGlyph&) = delete;
		RgGUIGlyph& operator=(const RgGUIGlyph&) = delete;

		bool m_bIsValid = false;
		RgFont * m_pfont = nullptr;
	};
}