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

	class RgGraphicsPipelineStage {
	public:
		static const unsigned int None = 0;
		static const unsigned int Vertex = 1 << 1;
		static const unsigned int Hull = 1 << 2;
		static const unsigned int Tessellator = 1 << 3;
		static const unsigned int Domain = 1 << 4;
		static const unsigned int Geometry = 1 << 5;
		static const unsigned int Rasterizer = 1 << 6;
		static const unsigned int Pixel = 1 << 7;
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