#pragma once
#include "rg_inc.h"

namespace rg {

	enum class RgImageType
	{
		Raw,
		Targa,
		PNG,
	};

	enum class RgImageFormat {
		NONE,
		R8G8B8A8,
		R8G8B8,
	};

	class RgImageLoader;

	class RgImage 
	{
	public:
		static RgImage* RgImageLoad(std::wstring filename, RgImageType imgtype);
		static bool RgImageSave(std::wstring filename, RgImage* img,RgImageType imgtype);
		static bool RgImageSave(std::wstring filename, unsigned char* data, unsigned int width, unsigned int height, RgImageType imgtype, RgImageFormat format);
		static RgImage* Craete(const unsigned int& width, const unsigned int& height, const RgImageFormat&);

		void Release();
		unsigned int GetWidth();
		unsigned int GetHeight();
		unsigned char* GetData();
		size_t GetDataSize() const;
		unsigned int GetChannel();

		virtual ~RgImage();
	protected:
		RgImage();
		RgImage(const unsigned int& width, const unsigned int&height, const RgImageFormat& format);
		RgImage(const RgImage&) = delete;
		RgImage& operator= (const RgImage&) = delete;

		unsigned char* m_pData = nullptr;
		size_t m_DataSize = 0;
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		RgImageFormat m_format = RgImageFormat::NONE;
	public:
		friend class RgImageLoader;
	};
}