#pragma once
#include "rggraphics_inc.h"
#include "rg_graphicsAPI.h"

namespace rg {

	enum class RgDepthStencilOp {
		KEEP = 1,
		ZERO = 2,
		REPLACE = 3,
		INCR_SAT = 4,
		DECR_SAT = 5,
		INVERT = 6,
		INCR = 7,
		DECR = 8,
	};



	enum class RgDepthWriteMask {
		MASK_ZERO = 0,
		MASK_ALL = 1,
	};

	struct RgDepthStencilOperation {
		RgDepthStencilOp StencilFailOp = RgDepthStencilOp::KEEP;
		RgDepthStencilOp StencilDepthFailOp = RgDepthStencilOp::KEEP;
		RgDepthStencilOp StencilPassOp = RgDepthStencilOp::KEEP;
		RgGraphicsComparisonFunc StencilFunc = RgGraphicsComparisonFunc::ALWAYS;
	};

	struct RgDepthStencilSettings {
		bool DepthEnable = true;
		RgDepthWriteMask DepthWriteMask = RgDepthWriteMask::MASK_ALL;
		RgGraphicsComparisonFunc DepthFunc = RgGraphicsComparisonFunc::LESS;

		bool StencilEnable = true;
		UINT8 StencilReadMask = 0xFF;
		UINT8 StencilWriteMask = 0xFF;
		RgDepthStencilOperation FrontFace;
		RgDepthStencilOperation BackFace;
	};

	class RgDepthStencilState {

	public:
		RgDepthStencilState(const RgDepthStencilSettings& settings) :m_settings(settings) {

		}
		virtual ~RgDepthStencilState();

		virtual void Release();

	protected:
		const RgDepthStencilSettings m_settings;
	private:
		RgDepthStencilState(const RgDepthStencilState&) = delete;
		RgDepthStencilState& operator=(const RgDepthStencilState&) = delete;
	};
}