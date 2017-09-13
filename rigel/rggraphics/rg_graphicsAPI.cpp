#include "rggraphics.h"
#include "rg_graphicsAPI.h"
#include "rg_graphicscontext.h"
#include "rg_graphicsContextDX11.h"

namespace rg {

	RgGraphicsContext * RgGraphicsAPI::s_pGraphicContext;

	RgGraphicsContext* rg::RgGraphicsAPI::InitAPI(RG_GRAPHICS_API apitype, RG_GRAPHICS_INIT_SETTINGS* settings)
	{
		switch (apitype)
		{
		case RG_GRAPHICS_API_OPENGL:
			break;
		case RG_GRAPHICS_APY_DX11:
			s_pGraphicContext = new RgGraphicsContextDX11();
			break;
		}

	
		s_pGraphicContext->init(settings);
		return s_pGraphicContext;
	}
	void RgGraphicsAPI::ReleaseAPI(RgGraphicsContext * ctx)
	{
		if (ctx != nullptr)
		{
			ctx->release();
			delete ctx;
		}
			
	}
	RgGraphicsAPI::~RgGraphicsAPI()
	{
		ReleaseAPI(s_pGraphicContext);
		s_pGraphicContext = nullptr;
	}
}


