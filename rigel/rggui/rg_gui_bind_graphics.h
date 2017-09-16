#pragma once
#include <rggraphics\rggraphics_inc.h>
#include <rggraphics\rg_graphicscontext.h>
#include <rggui\rg_gui_draw_buffer.h>
#include <rggraphics\rg_inputlayout.h>
#include <rggraphics\rg_command_list.h>
#include <memory>

namespace rg {

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
		void AfterResize();



	protected:

		unsigned int m_uintVertexBufferSize = RgGUIDrawBuffer::BUFFER_SIZE_INIT;
		unsigned int m_uintIndicesBufferSize = RgGUIDrawBuffer::BUFFER_SIZE_INIT * 2;

		RgRenderContext * m_pRenderCtx = nullptr;

		RgGUIContext * m_pGUICtx = nullptr;
		RgGraphicsContext * m_pGraphics = nullptr;
		RgCommandList * m_pCommandList = nullptr;
		
		RgBuffer * m_pBufferVertex = nullptr;
		RgBuffer * m_pBufferIndices = nullptr;
		RgBuffer* m_pBufferConst = nullptr;

		RgInputLayout * m_pInputLayout = nullptr;

		std::shared_ptr<RgShader> m_pShaderVertex = nullptr;
		std::shared_ptr<RgShader> m_pShaderPixel = nullptr;

	};
}