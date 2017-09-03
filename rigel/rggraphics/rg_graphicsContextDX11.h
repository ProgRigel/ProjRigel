#pragma once
#include "rg_graphicscontext.h"

namespace rg {
	class RgGraphicsContextDX11 : public RgGraphicsContext
	{
	protected:
		RgGraphicsContextDX11();
		~RgGraphicsContextDX11();

		void init();
		void release();

	public:
		friend class RgGraphicsAPI;

	};
}