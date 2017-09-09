#include "rg_image_loader.h"

namespace rg {

#pragma region targa
	struct IMAGE_TARGA_HEADER
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};
	RgImage* RgImageLoader::Load(FILE * fileptr, RgImageType imgtype)
	{
		RgImage* img = nullptr;

		switch (imgtype)
		{
		case rg::RgImageType::Raw:
			break;
		case rg::RgImageType::Targa:
			RgImageLoadTarga(fileptr, &img);
			break;
		case RgImageType::PNG:

			break;
		default:
			break;
		}
		return img;
	}
	bool RgImageLoader::RgImageLoadTarga(FILE * fileptr,RgImage** img)
	{
		int error, bpp, imagesize, index, i, j, k;
		IMAGE_TARGA_HEADER targaFileHeader;
		unsigned int count;
		unsigned char* targaImage;
		count = (unsigned int)fread(&targaFileHeader, sizeof(targaFileHeader), 1, fileptr);
		if (count != 1)
		{
			return false;
		}

		int height = (int)targaFileHeader.height;
		int width = (int)targaFileHeader.width;
		bpp = (int)targaFileHeader.bpp;

		if (bpp != 32)
		{
			std::cout << "current targa not support 24bit .tag file" << std::endl;
			return false;
		}

		imagesize = width*height * 4;
		targaImage = new unsigned char[imagesize];
		if (!targaImage)
		{
			return false;
		}

		count = (unsigned int)fread(targaImage, 1, imagesize, fileptr);
		if (count != imagesize)
		{
			return false;
		}

		error = fclose(fileptr);
		if (error != 0)
		{
			return false;
		}

		*img = new RgImage();
		unsigned char* m_data = new unsigned char[imagesize];

		index = 0;
		k = 0;

		for (j = 0; j<height; j++)
			for (i = 0; i < width; i++)
			{
				m_data[index] = targaImage[k + 2];
				m_data[index + 1] = targaImage[k + 1];
				m_data[index + 2] = targaImage[k + 0];
				m_data[index + 3] = targaImage[k + 3];

				k += 4;
				index += 4;
			}

		delete[] targaImage;
		targaImage = 0;
		(*img)->m_width = width;
		(*img)->m_height = height;
		(*img)->m_pData = m_data;
		(*img)->m_format = RgImageFormat::R8G8B8A8_UCHAR;

		return true;
	}


#pragma endregion
}


