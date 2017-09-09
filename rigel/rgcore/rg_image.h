#pragma once
#include "rg_inc.h"
#include <string>

namespace rg {

	enum class RgImageType
	{
		Raw,
		Targa,
		PNG,
	};

	enum class RgImageFormat {
		NONE,
		R8G8B8A8_UCHAR,
	};

	class RgImageLoader;

	class RgImage 
	{
	public:
		static RgImage* RgImageLoad(std::wstring filename, RgImageType imgtype);
		static void RgImageSave(std::wstring filename, RgImage* img);
		static void RgImageSave(std::wstring filename, unsigned char* data, unsigned int width, unsigned int height, RgImageType imgtype);

		void Release();
		unsigned int GetWidth();
		unsigned int GetHeight();
		unsigned char* GetData();


	protected:
		RgImage();
		virtual ~RgImage();
		RgImage(const RgImage&) = delete;
		RgImage& operator= (const RgImage&) = delete;

		unsigned char* m_pData = nullptr;
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		RgImageFormat m_format = RgImageFormat::NONE;
	public:
		friend class RgImageLoader;
	};
}