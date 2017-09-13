#pragma once
#include "rgcore.h"

#pragma warning(disable:4996)
#include <../libpng/png.h>
#pragma comment(lib,"libpng16.lib")
#pragma comment(lib,"zlib.lib")

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
		(*img)->m_format = RgImageFormat::R8G8B8A8;

		return true;
	}

	bool RgImageLoader::RgImageLoadPng(FILE * fileptr, RgImage ** img)
	{
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		auto info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			png_destroy_read_struct(&png_ptr, nullptr, nullptr);
			std::cout << "libPng init error" <<std::endl;
			return false;
		}

		setjmp(png_jmpbuf(png_ptr));
		png_init_io(png_ptr, fileptr);
		png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

		int m_width = png_get_image_width(png_ptr, info_ptr);
		int m_height = png_get_image_height(png_ptr, info_ptr);
		int m_colorType = png_get_color_type(png_ptr, info_ptr);
		bool m_alpha = ((m_colorType & PNG_COLOR_MASK_ALPHA) > 0);
		std::cout<< "image width:" << m_width << " height:" << m_height << " color:" << m_colorType << " alpha:" << m_alpha<<std::endl;

		(*img) = new RgImage();
		RgImage * rgimg = (*img);

		int bytesize = (m_alpha ? 4 : 3);
		size_t size = m_width * m_height * bytesize;
		int linesize = m_width* bytesize;
		unsigned char * data = new unsigned char[size];


		png_bytep * row_pointers = png_get_rows(png_ptr, info_ptr);

		int pos = 0;
		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < (bytesize * m_width); j += bytesize)
			{
				data[pos++] = row_pointers[i][j + 0];
				data[pos++] = row_pointers[i][j + 1];
				data[pos++] = row_pointers[i][j + 2];

				if (m_alpha)
					data[pos++] = row_pointers[i][j + 3];
			}
		}

		rgimg->m_pData = data;
		rgimg->m_width = m_width;
		rgimg->m_height = m_height;
		rgimg->m_format = m_alpha ? RgImageFormat::R8G8B8A8 : RgImageFormat::R8G8B8;

		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		fclose(fileptr);

		std::cout << "libPng load success" <<std::endl;
		return true;
	}

	bool RgImageLoader::RgImageWritePng(const WCHAR * filename, unsigned char * data, unsigned int width, unsigned int height, RgImageFormat format)
	{
		FILE * fileptr;
		png_structp png_ptr;
		png_infop info_ptr;


		_bstr_t b(filename);
		const char* c = b;

		fileptr = fopen(c, "wb");
		if (fileptr)
		{
			png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			info_ptr = png_create_info_struct(png_ptr);
			if (info_ptr == nullptr)
			{
				std::cout << "create png info_ptr error";
				return false;
			}

			png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

			//data
			const char *b = reinterpret_cast<char*>(data);

			png_byte ** row_pointers = (png_byte**)png_malloc(png_ptr, height * sizeof(png_byte *));
			for (unsigned int y = 0; y < height; y++)
			{
				png_byte * row = (png_byte*)png_malloc(png_ptr, sizeof(unsigned char) * width * 4);
				row_pointers[y] = row;

				if (format == RgImageFormat::R8G8B8)
				{
					for (unsigned int x = 0; x < width; x++)
					{
						row[x * 4] = b[y*width * 3 + x * 3];
						row[x * 4 + 1] = b[y*width * 3 + x * 3 + 1];
						row[x * 4 + 2] = b[y*width * 3 + x * 3 + 2];
						row[x * 4 + 3] = 255;
					}
				}
				else
				{
					for (unsigned int x = 0; x < width; x++)
					{
						row[x * 4] = b[y*width * 4 + x * 4];
						row[x * 4 + 1] = b[y*width * 4 + x * 4 + 1];
						row[x * 4 + 2] = b[y*width * 4 + x * 4 + 2];
						row[x * 4 + 3] = b[y*width * 4 + x * 4 + 3];
					}
				}


			}

			png_init_io(png_ptr, fileptr);
			png_set_rows(png_ptr, info_ptr, row_pointers);
			png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

			int status = 0;
			for (unsigned int y = 0; y < height; y++)
			{
				png_free(png_ptr, row_pointers[y]);
			}
			png_free(png_ptr, row_pointers);

			png_destroy_write_struct(&png_ptr, &info_ptr);

			fclose(fileptr);

			return true;
		}

		return false;
	}


#pragma endregion
}


