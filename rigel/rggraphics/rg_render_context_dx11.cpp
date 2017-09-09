#include "rg_render_context_dx11.h"
#include "rg_bufferDX11.h"
#include "rg_shaderDX11.h"
#include "rg_inputlayout.h"
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

			RgLogW() << "set index buffer";
			break;
		case rg::RgBufferBind::VertexBuffer:
			m_pDeviceContext->IASetVertexBuffers(0, 1, &bufferdx11->m_pbuffer,&stride,&offset);
			RgLogW() << "set vertex buffer";
			break;
		default:
			break;
		}

		RgLogD() << "set buffer done!";
	}
	void RgRenderContextDX11::InputSetShader(std::shared_ptr<RgShader> shader)
	{
		RgShader * rgshader = shader.get();
		RgShaderDX11 * rgshaderdx11 = dynamic_cast<RgShaderDX11*>(rgshader);

		switch (shader->GetShaderEntry())
		{
		case RG_SHADER_ENTRY::Vertex:
			m_pDeviceContext->VSSetShader(rgshaderdx11->m_pVertexShader, nullptr, 0);
			RgLogW() << "set vertex shader";
			break;
		case RG_SHADER_ENTRY::Pixel:
			m_pDeviceContext->PSSetShader(rgshaderdx11->m_pPixelShader, nullptr, 0);
			RgLogW() << "set pixel shader";
		default:
			break;
		}
	}
	void RgRenderContextDX11::InputSetPrimitiveTopology()
	{
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	void RgRenderContextDX11::InputSetInputLayout(RgInputLayout * layout)
	{
		ID3D11InputLayout * dx11layout = (ID3D11InputLayout*)layout->pLayout;
		m_pDeviceContext->IASetInputLayout(dx11layout);
	}
	void RgRenderContextDX11::DrawIndexed(unsigned int size)
	{
	}
	void RgRenderContextDX11::Draw()
	{
		m_pDeviceContext->DrawIndexed(3, 0, 0);
	}
	RgRenderContextDX11::RgRenderContextDX11()
	{
	}

	RgRenderContextDX11::~RgRenderContextDX11()
	{
		m_pDeviceContext = nullptr;
	}

}
