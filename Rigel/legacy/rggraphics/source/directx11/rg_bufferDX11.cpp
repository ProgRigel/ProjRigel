#include "rggraphics.h"
#include "rggraphics_inc.h"
#include "directx11\rg_bufferDX11.h"
#include "directx11\rg_render_context_dx11.h"
#include "directx11\rg_graphicsContextDX11.h"
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
		}
		
	}

	void RgBufferDX11::SetData(RgRenderContext * renderctx, void * pdata, unsigned int size, RgGraphicsBufferMap maptype)
	{

		SetData(renderctx, 1, &pdata, &size, maptype);
		
	}

	void RgBufferDX11::SetData(RgRenderContext * renderctx,unsigned int datacount,void ** pdata, unsigned int* size, RgGraphicsBufferMap maptype) {

		auto ctx = dynamic_cast<RgRenderContextDX11*>(renderctx);
		if (ctx == nullptr) return;

		assert(m_pbuffer);

		D3D11_MAP dxmap = D3D11_MAP_WRITE;
		if (maptype == RgGraphicsBufferMap::WriteDiscard)
			dxmap = D3D11_MAP_WRITE_DISCARD;
		else if (maptype == RgGraphicsBufferMap::WriteNoOverride) {
			dxmap = D3D11_MAP_WRITE_NO_OVERWRITE;
		}

		D3D11_MAPPED_SUBRESOURCE bufferres;
		{
			HRESULT hr = ctx->m_pDeviceContext->Map(m_pbuffer, 0, dxmap, 0, &bufferres);
			if (hr != S_OK) {
				RgLogE() << "map buffer data error " << HR_CODE(hr);
				return;
			}
			auto dataptr = bufferres.pData;

			unsigned int sizeaccu = 0;
			for (unsigned int i = 0; i < datacount; i++) {
				memcpy(((byte*)dataptr + sizeaccu), pdata[i], size[i]);// make sure buffer allocates ...
				sizeaccu += size[i];
			}
			ctx->m_pDeviceContext->Unmap(m_pbuffer, 0);
		}
	}

	HRESULT RgBufferDX11::Create(ID3D11Device * device)
	{
		assert(device);
		auto hr = device->CreateBuffer(&m_bufferdesc, nullptr, &m_pbuffer);
		if (hr != S_OK) {
			RgLogE() << "create buffer error:" << hr;
			m_pbuffer = nullptr;
		}
		return hr;
	}

}
