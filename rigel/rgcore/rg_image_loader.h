#pragma once
#include "rg_image.h"
namespace rg {

	class RgImage;

	class RgImageLoader
	{
	public:
		static RgImage* Load(FILE * fileptr, RgImageType imgtype);

		static bool RgImageLoadTarga(FILE *fileptr, RgImage** img);
	};

	

}