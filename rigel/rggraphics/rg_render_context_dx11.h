#pragma once
#include "rg_graphicsAPI.h"
#include "rg_render_context.h"
#include <d3d11.h>

namespace rg {
	class RgGraphicsContextDX11;

	class RgRenderContextDX11 : public RgRenderContext {

	public:
		void InputSetBuffer(RgBuffer* buffer);
	protected:
		RgRenderContextDX11();
		~RgRenderContextDX11();


		ID3D11DeviceContext *m_pDeviceContext = nullptr;
	public:
		friend class RgGraphicsContextDX11;
		friend class RgBufferDX11;
	};
}