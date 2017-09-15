#include "rggui.h"
#include "rg_gui_bind_graphics.h"
#include "rg_gui_context.h"

#include <rggraphics\rg_shader.h>
#include <rggraphics\rg_buffer.h>

namespace rg {

	RgGUIBindGraphics::RgGUIBindGraphics(RgGUIContext * gui, RgGraphicsContext * graphics)
	{
		m_pGUICtx = gui;
		m_pGraphics = graphics;
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
	}
}


