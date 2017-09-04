#pragma once
#include "rg_graphicscontext.h"


namespace rg {

	enum RG_GRAPHICS_API
	{
		RG_GRAPHICS_API_OPENGL,
		RG_GRAPHICS_APY_DX11,
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