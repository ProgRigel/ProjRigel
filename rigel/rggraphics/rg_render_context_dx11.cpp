#include "rg_render_context_dx11.h"
#include "rg_bufferDX11.h"

namespace rg {
	void RgRenderContextDX11::InputSetBuffer(RgBuffer* buffer)
	{
		unsigned int stride = buffer->GetSettings().Stride;
		unsigned int offset = 0;

		auto bindtype = buffer->GetSettings().BindFlag;
		auto bufferdx11 = dynamic_cast<RgBufferDX11*>(buffer);
		switch (bindtype)
		{
		case rg::RgBufferBind::IndexBuffer:
			m_pDeviceContext->IASetIndexBuffer(bufferdx11->m_pbuffer, DXGI_FORMAT_R32_UINT, 0);
			break;
		case rg::RgBufferBind::VertexBuffer:
			m_pDeviceContext->IASetVertexBuffers(0, 1, &bufferdx11->m_pbuffer,&stride,&offset);
			break;
		default:
			break;
		}

		RgLogD() << "set buffer done!";
	}
	RgRenderContextDX11::RgRenderContextDX11()
	{
	}

	RgRenderContextDX11::~RgRenderContextDX11()
	{
		m_pDeviceContext = nullptr;
	}

}
