#pragma once
#include "rggraphics_inc.h"

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
		R32G32B32_FLOAT = 2,
		R32G32B32A32_FLOAT = 3,
		R8G8B8A8_UNORM = 4,
		D24_UNORM_S8_UINT = 5,
	};

	enum class RgGraphicsBindFlag {
		VertexBuffer,
		IndexBuffer,
		ConstantBuffer,
		ShaderResource,
		StreamOutput,
		RenderTarget,
		DepthStencil,
		UnorderedAccess,
		Decoder,
		VideoEncoder,
	};

	enum class RgGraphicsPipelineStage {
		None = 0,
		Vertex = 1 << 1,
		Hull = 1 << 2,
		Tessellator = 1 << 3,
		Domain = 1 << 4,
		Geometry = 1 << 5,
		Rasterizer = 1 << 6,
		Pixel = 1 << 7,
	};

	enum class RgGraphicsComparisonFunc
	{
		NEVER = 1,
		LESS = 2,
		EQUAL = 3,
		LESS_EQUAL = 4,
		GREATER = 5,
		NOT_EQUAL = 5,
		GREATER_EQUAL = 7,
		ALWAYS = 8,
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