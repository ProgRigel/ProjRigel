#pragma once

namespace rg {

	class RgGraphicsContext;
	struct RG_GRAPHICS_INIT_SETTINGS;

	enum RG_GRAPHICS_API
	{
		RG_GRAPHICS_API_OPENGL,
		RG_GRAPHICS_APY_DX11,
	};

	enum class RgGraphicsFormat {
		UNKNOWN = 0,
		R32G32_FLOAT = 1,
	};

	class RgGraphicsAPI
	{
	public:
		static RgGraphicsContext* InitAPI(RG_GRAPHICS_API apitype,RG_GRAPHICS_INIT_SETTINGS * settings);
		static void ReleaseAPI(RgGraphicsContext * ctx);
	private:
		RgGraphicsAPI();

		
		~RgGraphicsAPI();

	private:
		static RgGraphicsContext* s_pGraphicContext;
	};

	
}