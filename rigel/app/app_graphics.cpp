#include "stdafx.h"
#include "app_graphics.h"
#include <rggraphics\rg_render_context.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rggraphics\rg_graphicscontext.h>
#include <rggraphics\rg_inputlayout.h>
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_draw_buffer.h>
#include <rggui\rg_gui_context.h>

using namespace rg;

namespace editor {

	RigelAppGraphics::RigelAppGraphics()
	{
	}

	RigelAppGraphics::~RigelAppGraphics()
	{
		Release();
	}

	void RigelAppGraphics::Release()
	{
		RgGraphicsAPI::ReleaseAPI(m_pRgGraphicsCtx);
		m_pRgGraphicsCtx = nullptr;
	}


	void RigelAppGraphics::Init(RgWindow * window)
	{
		RG_GRAPHICS_INIT_SETTINGS settings;
		settings.BufferHeight = window->getHeight();
		settings.BufferWidth = window->getWidth();
		settings.OutputWindow = (HWND)window->getHandler();
		settings.Windowed = true;

		m_pRgGraphicsCtx = RgGraphicsAPI::InitAPI(RG_GRAPHICS_API::RG_GRAPHICS_APY_DX11, &settings);

		//register callback
		window->EventOnResize.connect<RgGraphicsContext, &RgGraphicsContext::resizeBuffer>(m_pRgGraphicsCtx);

		RgGUIContext * guictx = nullptr;
		RgGUI::CreateRgGUIContext(&guictx);
		guictx->DrawRect(RgVec2(.0f, .0f), RgVec2(.5f, .3f));
		auto guibuf = guictx->GetDrawBuffer();

		//init draws
		{
			RgBufferSettings bufferVertexDesc;
			bufferVertexDesc.ByteWidth = guibuf->GetVertexCount() * sizeof(RgGUIVertex);
			bufferVertexDesc.BindFlag = RgBufferBind::VertexBuffer;
			bufferVertexDesc.Usage = RgBufferUsage::Dynamic;
			bufferVertexDesc.Stride = sizeof(RgGUIVertex);
			m_pBufferUIvertex = m_pRgGraphicsCtx->CreateBuffer(bufferVertexDesc);


			RgLogD() << "VS:" << (unsigned int)sizeof(RgGUIVertex) << (unsigned int)(guibuf->GetVertexCount() * sizeof(RgGUIVertex));
			m_pBufferUIvertex->SetData(m_pRgGraphicsCtx->GetRenderContext(), guibuf->GetDataPtr(), guibuf->GetVertexCount() * sizeof(RgGUIVertex));

			//float data[8];
			//data[0] = 0.0f;
			//data[1] = 1.0f;
			//data[2] = 0.0f;
			//data[3] = 0.0f;
			//data[4] = 1.0f;
			//data[5] = 0.0f;
			//data[6] = 1.0f;
			//data[7] = 1.0f;
			//m_pBufferUIvertex->SetData(m_pRgGraphicsCtx->GetRenderContext(), &data, sizeof(data));
		}

		{
			RgBufferSettings bufferIndicesDesc;
			bufferIndicesDesc.ByteWidth = 6 * sizeof(unsigned int);
			bufferIndicesDesc.BindFlag = RgBufferBind::IndexBuffer;
			bufferIndicesDesc.Usage = RgBufferUsage::Dynamic;
			bufferIndicesDesc.Stride = sizeof(unsigned int);
			m_pBufferUIindices = m_pRgGraphicsCtx->CreateBuffer(bufferIndicesDesc);

			unsigned int datai[6]{ 0,2,1,0,3,2 };
			m_pBufferUIindices->SetData(m_pRgGraphicsCtx->GetRenderContext(), &datai, sizeof(datai));
		}
		//const buffer
		{
			RgBufferSettings bufferconstDesc;
			bufferconstDesc.ByteWidth = sizeof(float) * 4;
			bufferconstDesc.BindFlag = RgBufferBind::ConstBuffer;
			bufferconstDesc.Usage = RgBufferUsage::Dynamic;
			bufferconstDesc.Stride = sizeof(float) * 4;
			m_pBufferUIconst = m_pRgGraphicsCtx->CreateBuffer(bufferconstDesc);

			float color[4] = {
				1.0f,1.0f,0.2f,1.0f
			};
			m_pBufferUIconst->SetData(m_pRgGraphicsCtx->GetRenderContext(), &color, sizeof(color));
		}

		//create shader

		RgShaderOptions options;
		options.ShaderEntry = RG_SHADER_ENTRY::Vertex;
		options.EntryPoint = "main";
		options.ShaderTarget = "vs_4_0";
		std::wstring fpath = GetWorkDirectory();
		fpath = fpath.append(L"/Data/Res/vs.hlsl");
		RgLogD() << fpath;
		m_pShaderUIvertex = m_pRgGraphicsCtx->CompileShaderFromFile(fpath, options);

		RgShaderOptions options1;
		options1.ShaderEntry = RG_SHADER_ENTRY::Pixel;
		options1.EntryPoint = "main";
		options1.ShaderTarget = "ps_4_0";
		std::wstring fpath1 = GetWorkDirectory();
		fpath1 = fpath1.append(L"/Data/Res/ps.hlsl");
		RgLogD() << fpath1;
		m_pShaderUIfragment = m_pRgGraphicsCtx->CompileShaderFromFile(fpath1, options1);

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

		m_pInputlayout = m_pRgGraphicsCtx->CreateInputLayout(layoute, 3, m_pShaderUIvertex);
		RG_ASSERT(m_pInputlayout);
		auto renderctx = m_pRgGraphicsCtx->GetRenderContext();
		renderctx->InputSetBuffer(m_pBufferUIvertex);
		renderctx->InputSetBuffer(m_pBufferUIindices);
		renderctx->InputSetBuffer(m_pBufferUIconst, RgGraphicsPipelineStage::Pixel);

		renderctx->InputSetInputLayout(m_pInputlayout);
		renderctx->InputSetShader(m_pShaderUIvertex);
		renderctx->InputSetShader(m_pShaderUIfragment);

		renderctx->InputSetPrimitiveTopology();

	}

	void RigelAppGraphics::Render()
	{
	}


}

