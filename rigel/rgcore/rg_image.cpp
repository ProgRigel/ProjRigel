#pragma once
#include "rgcore.h"
#include "rg_image.h"
#include "rg_image_loader.h"

namespace rg{
	RgImage * RgImage::RgImageLoad(std::wstring filename, RgImageType imgtype)
	{
		FILE *fileptr;
		int error = _wfopen_s(&fileptr, filename.c_str(), L"rb");
		if (error != 0)
		{
			return false;
		}
		
		RgImage* img = nullptr;

		switch (imgtype)
		{
		case rg::RgImageType::Raw:
			break;
		case rg::RgImageType::Targa:
			RgImageLoader::RgImageLoadTarga(fileptr, &img);
			break;
		case rg::RgImageType::PNG:
			RgImageLoader::RgImageLoadPng(fileptr, &img);
			break;
		default:
			break;
		}

		return img;

	}
	bool RgImage::RgImageSave(std::wstring filename, RgImage * img, RgImageType imgtype)
	{
		if (img == nullptr) return false;
		return RgImageSave(filename, img->m_pData, img->m_width, img->m_height, imgtype, img->m_format);
	}
	bool RgImage::RgImageSave(std::wstring filename, unsigned char * data, unsigned int width, unsigned int height, RgImageType imgtype, RgImageFormat format)
	{
		switch (imgtype)
		{
		case rg::RgImageType::Raw:
			break;
		case rg::RgImageType::Targa:
			break;
		case rg::RgImageType::PNG:
			return RgImageLoader::RgImageWritePng(filename.c_str(), data, width, height, format);
		default:
			break;
		}

		return false;
	}
	void RgImage::Release()
	{
		if (m_pData) delete[] m_pData;
		m_pData = nullptr;
	}
	unsigned int RgImage::GetWidth()
	{
		return m_width;
	}
	unsigned int RgImage::GetHeight()
	{
		return m_height;
	}
	unsigned char * RgImage::GetData()
	{
		return m_pData;
	}
	size_t RgImage::GetDataSize() const
	{
		RG_ASSERT(m_DataSize > 0);
		return m_DataSize;
	}
	RgImage::RgImage()
	{
		Release();
	}

	RgImage::~RgImage()
	{
		delete[] m_pData;
		m_pData = nullptr;
	}

}

