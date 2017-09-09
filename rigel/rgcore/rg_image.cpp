#pragma once
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
		return RgImageLoader::Load(fileptr, imgtype);
	}
	void RgImage::RgImageSave(std::wstring filename, RgImage * img)
	{

	}
	void RgImage::RgImageSave(std::wstring filename, unsigned char * data, unsigned int width, unsigned int height, RgImageType imgtype)
	{
	}
	void RgImage::Release()
	{
		if (m_pData) delete m_pData;
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
	RgImage::RgImage()
	{
		Release();
	}

	RgImage::~RgImage()
	{
		delete m_pData;
		m_pData = nullptr;
	}

}

