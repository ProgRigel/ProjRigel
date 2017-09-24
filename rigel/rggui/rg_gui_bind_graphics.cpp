#include "rggui.h"
#include "rg_gui_bind_graphics.h"
#include "rg_gui_context.h"

#include <rggraphics\rg_shader.h>
#include <rggraphics\rg_buffer.h>
#include <rggraphics\rg_render_context.h>
#include <rggraphics\rg_render_target.h>
#include <rggraphics\rg_texture.h>
namespace rg {

	RgGUIBindGraphics::RgGUIBindGraphics(RgGUIContext * gui, RgGraphicsContext * graphics)
	{
		m_pGUICtx = gui;
		m_pGraphics = graphics;

		m_pGraphics->EventBeforeResize.connect<RgGUIBindGraphics, &RgGUIBindGraphics::BeforeResize>(this);
		m_pGraphics->EventAfterResize.connect<RgGUIBindGraphics, &RgGUIBindGraphics::AfterResize>(this);

		InitGraphicsObj();
	}
	RgGUIBindGraphics::~RgGUIBindGraphics()
	{
		Release();
	}
	void RgGUIBindGraphics::Release()
	{
		ReleaseGraphicsObj();

		m_pGUICtx = nullptr;
		m_pGraphics = nullptr;
	}
	void RgGUIBindGraphics::OnRender()
	{
		//RgLogD() << "render";

		if (m_pGUICtx->IsDirty()) {
			m_pGUICtx->SetDirty(false);

			//RgLogD() << "dirty";

			//mapdata
			auto guibuf = m_pGUICtx->GetDrawBuffer();
			m_pBufferVertex->SetData(m_pGraphics->GetRenderContext(), guibuf->GetDataPtr(), guibuf->GetVertexCount() * sizeof(RgGUIVertex));

			auto indptr = guibuf->GetIndicesPtr();//???
			m_pBufferIndices->SetData(m_pGraphics->GetRenderContext(), indptr, guibuf->GetIndicesSize() * sizeof(unsigned int));

			if (guibuf->IsIndicesChanged()) {

				RgLogD() << "rebuild";

				ReBuildCommandList();
			}
		}


		if (m_pCommandList != nullptr) {
			m_pGraphics->GetRenderContext()->ExecuteCommandList(m_pCommandList, false);
		}
	}
	void RgGUIBindGraphics::ReBuildCommandList()
	{
		if (m_pCommandList != nullptr) {
			m_pCommandList->Release();
			delete m_pCommandList;
			m_pCommandList = nullptr;
		}

		auto rendertarget = m_pGraphics->GetRenderTarget();
		m_pRenderCtx->SetRenderTarget(rendertarget);

		m_pRenderCtx->SetRasterizerState(m_pRasterState);
		m_pRenderCtx->SetDepthStencilState(m_pDepthStencilState);
		m_pRenderCtx->SetViewPort(m_pGraphics->GetViewPortDefault());

		m_pRenderCtx->ClearRenderTarget(RgVec4(0.1f, 0.1f, 0.1f, 1.0f), rendertarget);
		m_pRenderCtx->ClearDepthStencil(rendertarget);

		m_pRenderCtx->InputSetBuffer(m_pBufferVertex);
		m_pRenderCtx->InputSetBuffer(m_pBufferIndices);
		m_pRenderCtx->InputSetBuffer(m_pBufferConst, RgGraphicsPipelineStage::Pixel);
		m_pRenderCtx->InputSetBuffer(m_pBufferConst, RgGraphicsPipelineStage::Vertex);

		m_pRenderCtx->InputSetInputLayout(m_pInputLayout);
		m_pRenderCtx->InputSetShader(m_pShaderVertex);
		m_pRenderCtx->InputSetShader(m_pShaderPixel);

		m_pRenderCtx->InputSetPrimitiveTopology();

		m_pRenderCtx->SetShaderTexture(m_pTextureFont,RgGraphicsPipelineStage::Pixel);

		m_pRenderCtx->DrawIndexed(m_pGUICtx->GetDrawBuffer()->GetIndicesSize());

		bool suc = m_pRenderCtx->FinishCommandList(false, &m_pCommandList);
		if (!suc) {
			RgLogE() << "create command list error";
		}
	}
	void RgGUIBindGraphics::InitGraphicsObj()
	{
		////////////// RenderContext

		m_pRenderCtx = m_pGraphics->CreateDeferredContext();
		
		//rasterstate

		{
			RgRasterizerSettings rssetings;
			rssetings.AntialiasedLine = false;
			rssetings.CullMode = RgRasterizerCullMode::CULL_NONE;
			rssetings.FillMode = RgRasterizerFillMode::FILL_SOLID;
			rssetings.DepthBias = 0;
			rssetings.DepthBiasClamp = 0;
			rssetings.DepthClipEnable = true;
			rssetings.MultisampleEnable = false;
			rssetings.ScissorEnable = false;
			rssetings.SlopeScaledDepthBias = 0;
			m_pRasterState = m_pGraphics->CreateRasterizerState(rssetings);

			RG_ASSERT(m_pRasterState);
		}
		

		///////////////////// Buffers

		// VertexBuffer;
		{
			RgBufferSettings bufferVertexDesc;
			bufferVertexDesc.ByteWidth = m_uintVertexBufferSize * sizeof(RgGUIVertex);
			bufferVertexDesc.BindFlag = RgBufferBind::VertexBuffer;
			bufferVertexDesc.Usage = RgBufferUsage::Dynamic;
			bufferVertexDesc.Stride = sizeof(RgGUIVertex);
			m_pBufferVertex = m_pGraphics->CreateBuffer(bufferVertexDesc);
		}

		// IndicesBuffer;
		{
			RgBufferSettings bufferIndicesDesc;
			bufferIndicesDesc.ByteWidth = m_uintIndicesBufferSize * sizeof(unsigned int);
			bufferIndicesDesc.BindFlag = RgBufferBind::IndexBuffer;
			bufferIndicesDesc.Usage = RgBufferUsage::Dynamic;
			bufferIndicesDesc.Stride = sizeof(unsigned int);
			bufferIndicesDesc.DX_AccessFlag = D3D11_CPU_ACCESS_WRITE;
			m_pBufferIndices = m_pGraphics->CreateBuffer(bufferIndicesDesc);
		}

		//ConstBuffer
		{
			RgBufferSettings bufferconstDesc;
			bufferconstDesc.ByteWidth = sizeof(RgGUIConstantData);
			bufferconstDesc.BindFlag = RgBufferBind::ConstBuffer;
			bufferconstDesc.Usage = RgBufferUsage::Dynamic;
			bufferconstDesc.Stride = 0;
			m_pBufferConst = m_pGraphics->CreateBuffer(bufferconstDesc);
		}

		//////////////////// Shaders

		//VertexShader
		{
			RgShaderOptions optionsVertex;
			optionsVertex.ShaderEntry = RG_SHADER_ENTRY::Vertex;
			optionsVertex.EntryPoint = "main";
			optionsVertex.ShaderTarget = "vs_4_0";
			std::wstring fpath = GetWorkDirectory();
			fpath = fpath.append(L"/Data/Res/vs.hlsl");
			m_pShaderVertex = m_pGraphics->CompileShaderFromFile(fpath, optionsVertex);
		}
		//PixelShader
		{
			RgShaderOptions optionsPixel;
			optionsPixel.ShaderEntry = RG_SHADER_ENTRY::Pixel;
			optionsPixel.EntryPoint = "main";
			optionsPixel.ShaderTarget = "ps_4_0";
			std::wstring fpath = GetWorkDirectory();
			fpath = fpath + L"/Data/Res/ps.hlsl";
			m_pShaderPixel = m_pGraphics->CompileShaderFromFile(fpath, optionsPixel);
		}

		/////////////////// InputLayout
		{
			RgInputLayoutElement layoute[3];
			layoute[0].SemanticName = "POSITION";
			layoute[0].SemanticIndex = 0;
			layoute[0].Format = RgGraphicsFormat::R32G32B32A32_FLOAT;
			layoute[0].InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
			layoute[0].InputSlot = 0;
			layoute[0].AlignedByteOffset = 0;

			layoute[1].SemanticName = "COLOR";
			layoute[1].SemanticIndex = 0;
			layoute[1].Format = RgGraphicsFormat::R32G32B32A32_FLOAT;
			layoute[1].InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
			layoute[1].InputSlot = 0;
			layoute[1].AlignedByteOffset = 0xffffffff;

			layoute[2].SemanticName = "TEXCOORD";
			layoute[2].SemanticIndex = 0;
			layoute[2].Format = RgGraphicsFormat::R32G32_FLOAT;
			layoute[2].InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
			layoute[2].InputSlot = 0;
			layoute[2].AlignedByteOffset = 0xffffffff;

			m_pInputLayout = m_pGraphics->CreateInputLayout(layoute, 3, m_pShaderVertex);
		}

		//depth stencil sstate
		{
			RgDepthStencilSettings dssettings;
			dssettings.DepthEnable = true;
			dssettings.DepthFunc = RgGraphicsComparisonFunc::LESS_EQUAL;
			dssettings.DepthWriteMask = RgDepthWriteMask::MASK_ALL;
			dssettings.StencilEnable = false;
			m_pDepthStencilState = m_pGraphics->CreateDepthStencilState(dssettings);
			RG_ASSERT(m_pDepthStencilState);
		}

		//textures
		{
			RgTextureSettings texsettings;
			texsettings.Width = 256;
			texsettings.Height = 256;
			texsettings.SampleDesc.Count = 1;
			texsettings.SampleDesc.Quality = 0;
			texsettings.Format = RgGraphicsFormat::R8G8B8A8_UNORM;
			texsettings.DX_CPUAccessFlag = 0;
			texsettings.DX_MiscFlags = 0;
			texsettings.Usage = RgGraphicsUsage::DEFAULT;
			texsettings.BindFlags = RgGraphicsBindFlag::ShaderResource;
			texsettings.ArraySize = 1;
			texsettings.MipLevels = 1;

			m_pTextureFont = m_pGraphics->CreateTexture(texsettings);
		}

		//PixelShader
		{
			RgShaderOptions shaderFont;
			shaderFont.ShaderEntry = RG_SHADER_ENTRY::Pixel;
			shaderFont.EntryPoint = "main";
			shaderFont.ShaderTarget = "ps_4_0";
			std::wstring fpath = GetWorkDirectory();
			fpath = fpath + L"/Data/Res/ps.hlsl";
			m_pShaderPixelText = m_pGraphics->CompileShaderFromFile(fpath, shaderFont);
		}
		
		auto guibuf = m_pGUICtx->GetDrawBuffer();
		m_pBufferVertex->SetData(m_pGraphics->GetRenderContext(), guibuf->GetDataPtr(), guibuf->GetVertexCount() * sizeof(RgGUIVertex));

		auto indptr = guibuf->GetIndicesPtr();//???
		m_pBufferIndices->SetData(m_pGraphics->GetRenderContext(), indptr, guibuf->GetIndicesSize() * sizeof(unsigned int));



		float bwidth =2.0f /m_pGraphics->GetRenderTarget()->BufferWidth;
		float bheight = -2.0f / m_pGraphics->GetRenderTarget()->BufferHeight;
		constantData.color = RgVec4(1.0f, 0.3f, 0.5f, 1.0f);
		constantData.mtx.m1 = RgVec4(bwidth, .0, .0,.0);
		constantData.mtx.m2 = RgVec4(.0f, bheight, .0f,.0f);
		constantData.mtx.m3 = RgVec4(0.0f,0.0f,1.0f/65535.0f,0.0f);
		constantData.mtx.m4 = RgVec4(-1.0f, 1.0f, .0f, 1.0f);
		m_pBufferConst->SetData(m_pGraphics->GetRenderContext(), &constantData, sizeof(constantData));

		ReBuildCommandList();

	}
	void RgGUIBindGraphics::ReleaseGraphicsObj()
	{
		if (m_pRenderCtx != nullptr) {
			m_pRenderCtx->Release();
			m_pRenderCtx = nullptr;
		}
		if (m_pCommandList != nullptr) {
			m_pCommandList->Release();
			delete m_pCommandList;
			m_pCommandList = nullptr;
		}

		if (m_pRasterState != nullptr) {
			m_pRasterState->Release();
			delete m_pRasterState;
			m_pRasterState = nullptr;
		}

		if (m_pShaderPixel != nullptr) {
			m_pShaderPixel->Release();
			m_pShaderPixel = nullptr;
		}
		if (m_pShaderVertex != nullptr) {
			m_pShaderVertex->Release();
			m_pShaderVertex = nullptr;
		}
		if (m_pBufferConst != nullptr) {
			m_pBufferConst->Release();
			m_pBufferConst = nullptr;
		}
		if (m_pBufferIndices != nullptr) {
			m_pBufferIndices->Release();
			m_pBufferIndices = nullptr;
		}
		if (m_pBufferVertex != nullptr) {
			m_pBufferVertex->Release();
			m_pBufferVertex = nullptr;
		}

		if (m_pInputLayout != nullptr) {
			delete m_pInputLayout;
			m_pBufferConst = nullptr;
		}

		if (m_pDepthStencilState != nullptr) {
			m_pDepthStencilState->Release();
			m_pDepthStencilState = nullptr;
		}

		if (m_pTextureFont != nullptr) {
			m_pTextureFont->Release();
			m_pTextureFont = nullptr;
		}

		if (m_pShaderPixelText != nullptr) {
			m_pShaderPixelText->Release();
			m_pShaderPixelText = nullptr;
		}

	}
	void RgGUIBindGraphics::BeforeResize()
	{
		if (m_pCommandList != nullptr) {
			m_pCommandList->Release();
			delete m_pCommandList;
			m_pCommandList = nullptr;
		}

		if (m_pRasterState != nullptr){
			m_pRasterState->Release();

			RgRasterizerSettings rssetings;
			rssetings.AntialiasedLine = false;
			rssetings.CullMode = RgRasterizerCullMode::CULL_BACK;
			rssetings.FillMode = RgRasterizerFillMode::FILL_SOLID;
			rssetings.DepthBias = 0;
			rssetings.DepthBiasClamp = 0;
			rssetings.DepthClipEnable = true;
			rssetings.MultisampleEnable = false;
			rssetings.ScissorEnable = false;
			rssetings.SlopeScaledDepthBias = 0;
			m_pRasterState = m_pGraphics->CreateRasterizerState(rssetings);

			RG_ASSERT(m_pRasterState);
		}
	}
	void RgGUIBindGraphics::AfterResize(unsigned int width,unsigned int height)
	{
		float bwidth = 2.0f / width;
		float bheight = -2.0f / height;

		constantData.mtx.m1 = RgVec4(bwidth, .0, .0, .0);
		constantData.mtx.m2 = RgVec4(.0, bheight, .0, .0);
		constantData.mtx.m3 = RgVec4(0.f, 0.f, 1.0f/65535.0f, 0.f);
		constantData.mtx.m4 = RgVec4(-2, 1, 0, 1);
		m_pBufferConst->SetData(m_pGraphics->GetRenderContext(), &constantData, sizeof(constantData));

		ReBuildCommandList();
	}
}


