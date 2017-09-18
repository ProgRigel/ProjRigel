#pragma once
#include "rg_buffer.h"
namespace rg {
	class RgGraphicsContextDX11;
	class RgBuffer;
	class RgRenderContext;

	class RgBufferDX11 : public RgBuffer {

	public:
		RgBufferDX11(RgBufferSettings settings);
		~RgBufferDX11();

		void Release();
		void SetData(RgRenderContext *renderctx, void *pdata, unsigned int size, RgGraphicsBufferMap maptype);
	protected:
		HRESULT Create(ID3D11Device * device);

		D3D11_BUFFER_DESC m_bufferdesc;
		ID3D11Buffer *m_pbuffer = nullptr;

	public:
		friend class RgGraphicsContextDX11;
		friend class RgRenderContextDX11;
	};
}