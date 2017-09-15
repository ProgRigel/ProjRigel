#pragma once
#include <rggraphics\rggraphics_inc.h>
#include <rggraphics\rg_graphicscontext.h>
#include <rggui\rg_gui_draw_buffer.h>

namespace rg {

	class RgGUIContext;

	class RgGUIBindGraphics {

	public:
		RgGUIBindGraphics(RgGUIContext *,RgGraphicsContext *);
		~RgGUIBindGraphics();

		void Release();


	private:
		void InitGraphicsObj();
		void ReleaseGraphicsObj();


	protected:

		unsigned int m_uintVertexBufferSize = RgGUIDrawBuffer::BUFFER_SIZE_INIT;
		unsigned int m_uintIndicesBufferSize = RgGUIDrawBuffer::BUFFER_SIZE_INIT * 2;

		RgGUIContext * m_pGUICtx = nullptr;
		RgGraphicsContext * m_pGraphics = nullptr;
		
		RgBuffer * m_pBufferVertex = nullptr;
		RgBuffer * m_pBufferIndices = nullptr;
		RgBuffer* m_pBufferConst = nullptr;

		RgShader * m_pShaderVertex = nullptr;
		RgShader * m_pShaderPixel = nullptr;

	};
}