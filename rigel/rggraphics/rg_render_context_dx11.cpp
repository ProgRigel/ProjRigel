#include "rggraphics.h"
#include "rg_render_context_dx11.h"
#include "rg_bufferDX11.h"
#include "rg_shaderDX11.h"
#include "rg_inputlayout.h"
#include "rg_command_list_dx11.h"
#include "rg_command_list.h"
#include "rg_buffer.h"
#include "rg_shader.h"
#include "rg_graphicsContextDX11.h"
#include "rg_viewport.h"
#include "rg_rasterizer_state.h"
#include "rg_rasterizer_state_dx11.h"
#include "rg_depthstencil_state_dx11.h"
#include "rg_render_target.h"
namespace rg {
	void RgRenderContextDX11::InputSetBuffer(RgBuffer* buffer, RgGraphicsPipelineStage tarstage)
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
		case rg::RgBufferBind::ConstBuffer:
			if (((unsigned int)tarstage & (unsigned int)RgGraphicsPipelineStage::Vertex) != 0)m_pDeviceContext->VSSetConstantBuffers(0, 1, &bufferdx11->m_pbuffer);
			if (((unsigned int)tarstage & (unsigned int)RgGraphicsPipelineStage::Pixel) != 0)m_pDeviceContext->PSSetConstantBuffers(0, 1, &bufferdx11->m_pbuffer);
		default:
			break;
		}
	}
	void RgRenderContextDX11::InputSetShader(std::shared_ptr<RgShader> shader)
	{
		RgShader * rgshader = shader.get();
		RgShaderDX11 * rgshaderdx11 = dynamic_cast<RgShaderDX11*>(rgshader);

		switch (shader->GetShaderEntry())
		{
		case RG_SHADER_ENTRY::Vertex:
			m_pDeviceContext->VSSetShader(rgshaderdx11->m_pVertexShader, nullptr, 0);
			break;
		case RG_SHADER_ENTRY::Pixel:
			m_pDeviceContext->PSSetShader(rgshaderdx11->m_pPixelShader, nullptr, 0);
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
		RG_ASSERT(layout);
		ID3D11InputLayout * dx11layout = (ID3D11InputLayout*)layout->pLayout;
		m_pDeviceContext->IASetInputLayout(dx11layout);
	}
	void RgRenderContextDX11::SetViewPort(const RgViewPort* viewport)
	{
		const D3D11_VIEWPORT* vp = (const D3D11_VIEWPORT*)(viewport);
		m_pDeviceContext->RSSetViewports(1, vp);
	}
	void RgRenderContextDX11::SetRasterizerState(RgRasterizerState * rs)
	{
		RgRasterizerStateDX11 * dxrs = dynamic_cast<RgRasterizerStateDX11*>(rs);
		if (dxrs == nullptr) {
			RgLogE() << "dxrs is null";
			return;
		}
		m_pDeviceContext->RSSetState(dxrs->m_ptr);
	}
	void RgRenderContextDX11::SetDepthStencilState(RgDepthStencilState *dss)
	{
		RgDepthStencilStateDX11 *dxdss = dynamic_cast<RgDepthStencilStateDX11*>(dss);
		RG_ASSERT(dxdss);
		if (dxdss == nullptr) {
			RgLogE() << "dxdss is null";
			return;
		}
		m_pDeviceContext->OMSetDepthStencilState(dxdss->m_state, 0);
	}
	void RgRenderContextDX11::SetRenderTarget(RgRenderTarget * rtarget)
	{
		ID3D11RenderTargetView * rtv =(ID3D11RenderTargetView*) rtarget->GetColorBufferPtr();
		ID3D11DepthStencilView * dsv = (ID3D11DepthStencilView*)rtarget->GetDepthBufferPtr();

		m_pDeviceContext->OMSetRenderTargets(1, &rtv, dsv);

	}
	void RgRenderContextDX11::ClearRenderTarget(RgVec4 color,RgRenderTarget * rtarget)
	{
		auto rtv =(ID3D11RenderTargetView*) rtarget->GetColorBufferPtr();
		if (rtv == nullptr) {
			RgLogE() << "render target rtv is null!";
			return;
		}
		const float c[4]{color.x,color.y,color.z,color.w};
		m_pDeviceContext->ClearRenderTargetView(rtv, c);
	}
	void RgRenderContextDX11::ClearDepthStencil(RgRenderTarget * rtarget)
	{
		auto dsv =(ID3D11DepthStencilView*) rtarget->GetDepthBufferPtr();
		if (dsv == nullptr) {
			RgLogE() << "render target dsv is null!";
			return;
		}
		m_pDeviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	void RgRenderContextDX11::DrawIndexed(unsigned int size)
	{
		m_pDeviceContext->DrawIndexed(size, 0, 0);
	}
	void RgRenderContextDX11::Draw()
	{
		m_pDeviceContext->DrawIndexed(3, 0, 0);
	}
	void RgRenderContextDX11::ClearState()
	{
		m_pDeviceContext->ClearState();
	}
	bool RgRenderContextDX11::FinishCommandList(bool restorectx, RgCommandList ** pcommandlist)
	{
		
		ID3D11CommandList * pcmdlist = nullptr;
		HRESULT hr = m_pDeviceContext->FinishCommandList(restorectx, &pcmdlist);
		if (hr != S_OK) {
			RgLogE() << "finish command list error"<<hr;
			return false;
		}
		RgCommandListDX11 * rgcmdlist = new RgCommandListDX11();
		rgcmdlist->m_pCommandList = pcmdlist;
		(*pcommandlist) = rgcmdlist;
		return true;
	}
	void RgRenderContextDX11::ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx)
	{
		if (pcommandlist == nullptr || m_bIsImmediateContext == false) {
			RgLogW() << "skip exec command list";
		}
		RgCommandListDX11 *pcmdlistdx11 = dynamic_cast<RgCommandListDX11*>(pcommandlist);
		RG_ASSERT(pcmdlistdx11 &&pcmdlistdx11->m_pCommandList);
		m_pDeviceContext->ExecuteCommandList(pcmdlistdx11->m_pCommandList, restorectx);

	}
	RgRenderContextDX11::RgRenderContextDX11(bool immedctx)
	{
		m_bIsImmediateContext = immedctx;
	}

	RgRenderContextDX11::~RgRenderContextDX11()
	{
		Release();
	}

	void RgRenderContextDX11::Release()
	{
		if (m_pDeviceContext != nullptr) {
			if (m_bIsImmediateContext == false) {
				m_pDeviceContext->Release();
			}
			m_pDeviceContext = nullptr;
			
		}
	}

}
