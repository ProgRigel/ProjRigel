#include "rggraphics.h"
#include "rg_texture_dx11.h"
#include "rg_render_context_dx11.h"
#include "rg_graphicsContextDX11.h"
namespace rg {
	void RgTextureDX11::SetRawData(void * data, unsigned int length)
	{
	}
	void RgTextureDX11::SetData(RgRenderContext * renderctx,void * data, size_t size)
	{
		auto ctx = dynamic_cast<RgRenderContextDX11*>(renderctx);
		RG_ASSERT(ctx != nullptr);
		RG_ASSERT(m_pd3d11tex2d);

		D3D11_MAPPED_SUBRESOURCE texres;
		HRESULT hr= ctx->GetDeviceContext()->Map(m_pd3d11tex2d, 0, D3D11_MAP_WRITE_DISCARD,0, &texres);
		if (hr != S_OK) {
			RgLogE() << L"map texture data error " << HrToMessage(hr);
			return;
		}
		auto  dataptr = texres.pData;
		memcpy(dataptr, data, size);
		ctx->GetDeviceContext()->Unmap(m_pd3d11tex2d, 0);
	}
	RgTextureDX11::~RgTextureDX11()
	{
		Release();
	}

	void RgTextureDX11::Release()
	{
		if (m_psrv != nullptr) {
			m_psrv->Release();
			m_psrv = nullptr;
		}

		if (m_pd3d11tex2d != nullptr) {
			m_pd3d11tex2d->Release();
			m_pd3d11tex2d = nullptr;
		}
	}
}

