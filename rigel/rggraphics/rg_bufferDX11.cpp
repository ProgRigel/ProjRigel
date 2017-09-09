#include "rg_bufferDX11.h"

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

		m_bufferdesc.ByteWidth = settings.ByteWidth;
		m_bufferdesc.CPUAccessFlags = settings.DX_AccessFlag;
		m_bufferdesc.MiscFlags = 0;
		m_bufferdesc.StructureByteStride = 0;
	}

	HRESULT RgBufferDX11::Create(ID3D11Device * device)
	{
		return device->CreateBuffer(&m_bufferdesc, nullptr, &m_pbuffer);
	}

}
