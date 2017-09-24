#pragma once
#include <string>
#include <vector>
#include "rg_image.h"

namespace rg {

	class RgFont;
	struct RgFontGlyph {
		unsigned int bitmapWidth;
		unsigned int bitmapHeight;
		unsigned int bitmapTop;
		unsigned int bitmapLeft;
		unsigned int advance;
	};

	class RgFontManager {
	private:
		RgFontManager();
		~RgFontManager();

	public:
		static void LoadFont(std::string ttfpath);
		static void UnloadFont(RgFont * font);
		static void Release();
	private:
		static bool CheckFTInited();

	private:
		static std::vector<RgFont*> s_vFonts;
	};


	class RgFont {
	protected:
		RgFont();
		~RgFont();
	public:
		bool IsValid() const;
		void SetPixelSize(const unsigned int size);
		void LoadGlyph(unsigned long c);

		void RenderToImage(const RgImage * img, const unsigned int posx, const unsigned int posy) const;
		void RenderText(std::string text, const RgImage* img, const unsigned int posx, const unsigned int posy);


		void Release();
	private:
		RgFont(const RgFont&) = delete;
		RgFont& operator=(const RgFont&) = delete;
	private:
		bool m_valid = false;
		unsigned int m_pixelsize = 0;
		void * m_pftface = nullptr;
		int m_layoutAscender = 0;
	public:
		RgFontGlyph m_glyph;

		friend class RgFontManager;
	};
}