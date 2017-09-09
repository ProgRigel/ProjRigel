#pragma once
#include "rg_graphicsContextDX11.h"

namespace rg {
	class RgGraphicsContextDX11;
	class RgBuffer;

	class RgBufferDX11 : public RgBuffer {

	public:
		RgBufferDX11(RgBufferSettings settings);
		~RgBufferDX11();

		virtual void Release();
	protected:
		HRESULT Create(ID3D11Device * device);

		D3D11_BUFFER_DESC m_bufferdesc;
		ID3D11Buffer *m_pbuffer = nullptr;

	public:
		friend class RgGraphicsContextDX11;
	};
}