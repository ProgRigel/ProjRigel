#pragma once
#include <Windows.h>


namespace rg {

	struct RG_GRAPHICS_INIT_SETTINGS
	{
		unsigned int BufferWidth = 0;
		unsigned int BufferHeight = 0;
		bool Windowed = true;
		HWND OutputWindow = nullptr;
	};


	class RgGraphicsContext
	{
	public:
		RgGraphicsContext();

		virtual void resizeBuffer(unsigned int width, unsigned int height);
		
	protected:
		virtual ~RgGraphicsContext();
		virtual void init(RG_GRAPHICS_INIT_SETTINGS * settings) = 0;
		virtual void release() = 0;

		RgGraphicsContext(const RgGraphicsContext&) = delete;
		const RgGraphicsContext& operator=(const RgGraphicsContext&) = delete;

		RG_GRAPHICS_INIT_SETTINGS m_settings;

	public:
		friend class RgGraphicsAPI;
	};
}
