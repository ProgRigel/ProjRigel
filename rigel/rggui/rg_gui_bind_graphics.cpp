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
	void RgGUIBindGraphics::InitGraphicsObj()
	{
		////////////// RenderContext

		m_pRenderCtx = m_pGraphics->CreateDeferredContext();

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
			bufferconstDesc.ByteWidth = sizeof(float) * 32;
			bufferconstDesc.BindFlag = RgBufferBind::ConstBuffer;
			bufferconstDesc.Usage = RgBufferUsage::Dynamic;
			bufferconstDesc.Stride = sizeof(float) * 4;
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


	}
	void RgGUIBindGraphics::ReleaseGraphicsObj()
	{
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
}


