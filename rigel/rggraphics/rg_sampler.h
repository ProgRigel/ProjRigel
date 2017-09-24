#pragma once
#include <rgcore\rg_math.h>
#include "rggraphics_inc.h"
#include "rg_graphicsAPI.h"

namespace rg {
	

	enum class RgGraphicsFilter {
		MinMagMipPoint,
		MinMagPointMipLinear,
		Anisotropic,
	};

	enum class RgGraphicsTextureAddressMode {
		Wrap = 1,
		Mirror = 2,
		Clamp = 3,
		Border = 4,
		MirrorOnce = 5,
	};

	struct RgGraphicsSamplerSettings {
		RgGraphicsFilter Filter = RgGraphicsFilter::MinMagMipPoint;
		RgGraphicsTextureAddressMode AddressU = RgGraphicsTextureAddressMode::Wrap;
		RgGraphicsTextureAddressMode AddressV = RgGraphicsTextureAddressMode::Wrap;
		RgGraphicsTextureAddressMode AddressW = RgGraphicsTextureAddressMode::Wrap;
		RgFloat MipLODBias = 0.0F;
		unsigned int MaxAnisotropy = 1;
		RgGraphicsComparisonFunc ComparisonFunc = RgGraphicsComparisonFunc::ALWAYS;
		RgVec4 BorderColor;
		RgFloat MinLOD = 0;
		RgFloat MaxLOD = 0;

	};

	class RgGraphicsSampler
	{
	public:
		RgGraphicsSampler(const RgGraphicsSamplerSettings& settings):m_settings(settings){}
		virtual ~RgGraphicsSampler();
		virtual void Release();

		RgGraphicsSampler(const RgGraphicsSampler&) = delete;
		RgGraphicsSampler& operator=(const RgGraphicsSampler&) = delete;

	protected:
		const RgGraphicsSamplerSettings m_settings;

	};
}
