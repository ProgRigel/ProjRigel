#pragma once
#include <rggraphics\rggraphics_inc.h>
#include <rggraphics\rg_graphicscontext.h>
#include <rggui\rg_gui_draw_buffer.h>
#include <rggraphics\rg_inputlayout.h>
#include <rggraphics\rg_command_list.h>
#include <rggraphics\rg_rasterizer_state.h>
#include <rggraphics\rg_depthstencil_state.h>
#include <rggraphics\rg_sampler.h>
#include <memory>

namespace rg {

	struct RgGUIConstantData {
		RgVec4 color;
		RgMatrix4x4 mtx;
	};

	class RgGUIContext;

	class RgGUIBindGraphics {

	public:
		RgGUIBindGraphics(RgGUIContext *,RgGraphicsContext *);
		~RgGUIBindGraphics();

		void Release();
		void OnRender();

		void ReBuildCommandList();


	private:
		void InitGraphicsObj();
		void ReleaseGraphicsObj();

		void BeforeResize();
		void AfterResize(unsigned int width, unsigned int height);


		void MapBufferData();


	protected:

		unsigned int m_uintVertexBufferSize = RgGUIVertexBuffer::VERTEX_SIZE_INIT;
		unsigned int m_uintIndicesBufferSize = RgGUIIndicesBuffer::INDICES_QUAD_INIT_COUNT *6;

		
		RgGUIContext * m_pGUICtx = nullptr;
		RgGraphicsContext * m_pGraphics = nullptr;

		RgRenderContext * m_pRenderCtx = nullptr;
		RgCommandList * m_pCommandList = nullptr;

		RgRasterizerState * m_pRasterState = nullptr;
		RgDepthStencilState * m_pDepthStencilState = nullptr;
		
		RgBuffer * m_pBufferVertex = nullptr;
		RgBuffer * m_pBufferIndices = nullptr;
		RgBuffer* m_pBufferConst = nullptr;

		RgInputLayout * m_pInputLayout = nullptr;

		std::shared_ptr<RgShader> m_pShaderVertex = nullptr;
		std::shared_ptr<RgShader> m_pShaderPixel = nullptr;

		std::shared_ptr<RgTexture> m_pTextureFont = nullptr;
		RgGraphicsSampler * m_pSampler = nullptr;
		std::shared_ptr<RgShader> m_pShaderPixelText = nullptr;

		RgGUIConstantData constantData;

		unsigned int m_vertexLastDrawCount = 0;
		unsigned int m_indicesLastSize = 0;

	};
}