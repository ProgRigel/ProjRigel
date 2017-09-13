#include "rggraphics.h"
#include "rg_bufferDX11.h"
#include "rg_render_context_dx11.h"
#include "rg_graphicsContextDX11.h"
#include "rg_buffer.h"
namespace rg {

	RgBufferDX11::RgBufferDX11(RgBufferSettings settings)
	{
		m_bufferdesc.Usage = D3D11_USAGE_DEFAULT;
		if (settings.Usage == RgBufferUsage::Dynamic)
			m_bufferdesc.Usage = D3D11_USAGE_DYNAMIC;

		m_bufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		if (settings.BindFlag == RgBufferBind::IndexBuffer)
			m_bufferdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		if (settings.BindFlag == RgBufferBind::VertexBuffer)
			m_bufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		if (settings.BindFlag == RgBufferBind::ConstBuffer)
			m_bufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		m_bufferdesc.ByteWidth = settings.ByteWidth;
		m_bufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;;
		m_bufferdesc.MiscFlags = 0;
		m_bufferdesc.StructureByteStride = 0;

	}

	RgBufferDX11::~RgBufferDX11()
	{
		Release();
	}

	void RgBufferDX11::Release()
	{
		if (m_pbuffer != nullptr) {
			m_pbuffer->Release();
			m_pbuffer = nullptr;
			RgLogW() << "release buffer";
		}
		
	}

	void RgBufferDX11::SetData(RgRenderContext * renderctx, void * pdata, unsigned int size)
	{
		auto ctx = dynamic_cast<RgRenderContextDX11*>(renderctx);
		if (ctx == nullptr) return;

		D3D11_MAPPED_SUBRESOURCE bufferres;
		{
			HRESULT hr = ctx->m_pDeviceContext->Map(m_pbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferres);
			if (hr != S_OK) {
				RgLogE() << "map buffer data error";
				return;
			}
			auto dataptr = bufferres.pData;
			memcpy(dataptr, pdata, size);
			ctx->m_pDeviceContext->Unmap(m_pbuffer, 0);
		}

		RgLogD() << "map buffer data succeed";
	}

	HRESULT RgBufferDX11::Create(ID3D11Device * device)
	{
		assert(device);
		auto hr = device->CreateBuffer(&m_bufferdesc, nullptr, &m_pbuffer);

		return hr;
	}

}
