#pragma once
#include "rggraphics_inc.h"
#include "rg_graphicsAPI.h"

namespace rg {

	enum class RgBlendOp {
		Add,
		Subtract,
		RevSubtract,
		Min,
		Max
	};

	enum class RgBlend
	{
		Zero,
		One,
		SrcColor,
		InvSrcColor,
		SrcAlpha,
		InvSrcAlpha,
		DstAlpha,
		InvDstAlpha,
		DstColor,
		InvDstColor,
		SrcAlphaSat,
		BlendFactor,
		InvBlendFactor,
		Src1Color,
		InvSrc1Color,
		Scr1Alpha,
		InvSrc1Alpha
	};

	enum class RgColorWriteMask
	{
		Red = 1,
		Green = 2,
		Blue = 4,
		Alpha = 8,
		All = ((((unsigned char)RgColorWriteMask::Alpha | (unsigned char)RgColorWriteMask::Red) | (unsigned char)RgColorWriteMask::Green) | (unsigned char)RgColorWriteMask::Blue)
	};

	struct RgRenderTargetBlendSetting
	{
		bool BlendEnable = false;
		RgBlend SrcBlend = RgBlend::SrcAlpha;
		RgBlend DstBlend = RgBlend::InvSrc1Alpha;
		RgBlendOp BlendOp = RgBlendOp::Add;

		RgBlend SrcBlendAlpha = RgBlend::One;
		RgBlend DstBlendAlpha = RgBlend::Zero;
		RgBlendOp BlendOpAlpha = RgBlendOp::Add;

		unsigned char RenderTargetWriteMask = (unsigned char)RgColorWriteMask::All;
	};

	struct RgBlendStateSettings
	{
		RgRenderTargetBlendSetting RenderTarget[8];
		bool DX_AlpahToConverageEnable;
		bool DX_IndependentBlendEnable;
	};

	class RgBlendState {
	public:
		RgBlendState(const RgBlendStateSettings& settings):m_settings(settings){}
		virtual ~RgBlendState();
		virtual void Release();
	private:
		RgBlendState(const RgBlendState&) = delete;
		RgBlendState& operator=(const RgBlendState&) = delete;

	protected:
		const RgBlendStateSettings& m_settings;
	};
}