#include "rggui.h"
#include "rg_gui_bind_graphics.h"
#include "rg_gui_context.h"

#include <rggraphics\rg_shader.h>
#include <rggraphics\rg_buffer.h>
#include <rggraphics\rg_render_context.h>

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
		m_pRenderCtx->SetViewPort(m_pGraphics->GetViewPortDefault());

		m_pRenderCtx->ClearRenderTarget(RgVec4(0.1f, 0.2f, 0.6f, 1.0f), rendertarget);
		m_pRenderCtx->ClearDepthStencil(rendertarget);

		m_pRenderCtx->InputSetBuffer(m_pBufferVertex);
		m_pRenderCtx->InputSetBuffer(m_pBufferIndices);
		m_pRenderCtx->InputSetBuffer(m_pBufferConst, RgGraphicsPipelineStage::Pixel);
		m_pRenderCtx->InputSetBuffer(m_pBufferConst, RgGraphicsPipelineStage::Vertex);

		m_pRenderCtx->InputSetInputLayout(m_pInputLayout);
		m_pRenderCtx->InputSetShader(m_pShaderVertex);
		m_pRenderCtx->InputSetShader(m_pShaderPixel);

		m_pRenderCtx->InputSetPrimitiveTopology();

		m_pRenderCtx->DrawIndexed(18);

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
			m_pBufferIndices = m_pGraphics->CreateBuffer(bufferIndicesDesc);
		}

		//ConstBuffer
		{
			RgBufferSettings bufferconstDesc;
			bufferconstDesc.ByteWidth = sizeof(float) * 16;
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
			layoute[0].Format = RgGraphicsFormat::R32G32B32_FLOAT;
			layoute[0].InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
			layoute[0].InputSlot = 0;
			layoute[0].AlignedByteOffset = 0;

			layoute[1].SemanticName = "COLOR";
			layoute[1].SemanticIndex = 0;
			layoute[1].Format = RgGraphicsFormat::R32G32B32_FLOAT;
			layoute[1].InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
			layoute[1].InputSlot = 0;
			layoute[0].AlignedByteOffset = 0xffffffff;

			layoute[2].SemanticName = "TEXCOORD";
			layoute[2].SemanticIndex = 0;
			layoute[2].Format = RgGraphicsFormat::R32G32_FLOAT;
			layoute[2].InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
			layoute[2].InputSlot = 0;
			layoute[0].AlignedByteOffset = 0xffffffff;

			m_pInputLayout = m_pGraphics->CreateInputLayout(layoute, 3, m_pShaderVertex);
		}


		m_pGUICtx->DrawRect(RgVec2(0.0f, .0f), RgVec2(70, 30.0f));
		m_pGUICtx->DrawRect(RgVec2(30.f, 100.f), RgVec2(200, 60.0f));
		m_pGUICtx->DrawRect(RgVec2(70.0f, 200.0f), RgVec2(50, 50.0f));
		
		auto guibuf = m_pGUICtx->GetDrawBuffer();
		m_pBufferVertex->SetData(m_pGraphics->GetRenderContext(), guibuf->GetDataPtr(), guibuf->GetVertexCount() * sizeof(RgGUIVertex));

		unsigned int datai[18]{ 0,1,2,0,2,3 };
		for (int i = 0; i < 3; i++) {
			datai[i * 6] = i * 4;
			datai[i * 6 + 1] = i * 4 + 1;
			datai[i * 6 + 2] = i * 4 + 2;
			datai[i * 6 + 3] = i * 4;
			datai[i * 6 + 4] = i * 4 + 2;
			datai[i * 6 + 5] = i * 4 + 3;
		}
		
		m_pBufferIndices->SetData(m_pGraphics->GetRenderContext(), &datai, sizeof(datai));


		RgGUIConstantData constantData;
		constantData.color = RgVec4(1.0f, 0.3f, 0.5f, 1.0f);
		constantData.mtx.m1 = RgVec3(2.0f / 800.0f, 0, 0);
		constantData.mtx.m2 = RgVec3(0,-2.0f/600.0f, 0);
		constantData.mtx.m3 = RgVec3(-1.0f,1.0f, 1.0f);
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
	void RgGUIBindGraphics::AfterResize()
	{
		ReBuildCommandList();
	}
}


