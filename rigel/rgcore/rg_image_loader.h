#pragma once
#include "rg_image.h"
namespace rg {

	class RgImage;

	class RgImageLoader
	{
	private:
		static bool RgImageLoadTarga(FILE *fileptr, RgImage** img);
		static bool RgImageLoadPng(FILE* fileptr, RgImage** img);

		static bool RgImageWritePng(const WCHAR * filename, unsigned char * data, unsigned int width, unsigned int height, RgImageFormat format);

	public:
		friend class RgImage;
	};

	

}