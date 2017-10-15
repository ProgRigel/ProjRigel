#pragma once
#include <rgcore\rgcore.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rgcore\rg_window.h>
#include <rggraphics\rg_buffer.h>
#include <rggraphics\rg_shader.h>
#include <rggraphics\rg_inputlayout.h>
#include <rggraphics\rg_command_list.h>
using namespace rg;

namespace editor {

	class RigelAppGraphics {

	public:
		RigelAppGraphics();
		~RigelAppGraphics();

		void Release();
		void Init(rg::RgWindow *window);
		void Render();


		void SetFullScreen(bool fullscreen) const;

	private:
		void OnEventResize(unsigned int width, unsigned int height);
		void onEventExitResize();
		void OnEventEnterResize();

	public:
		rg::RgGraphicsContext * m_pRgGraphicsCtx = nullptr;

	private:
		std::shared_ptr<RgShader> m_pShaderUIvertex;
		std::shared_ptr<RgShader> m_pShaderUIfragment;

		RgBuffer* m_pBufferUIvertex = nullptr;
		RgBuffer* m_pBufferUIindices = nullptr;
		RgBuffer* m_pBufferUIconst = nullptr;

		RgInputLayout * m_pInputlayout = nullptr;
		RgCommandList * m_pCommandList = nullptr;

		bool m_bOnDragResize = false;
		unsigned int m_uResizeWidth, m_uResizeHeight;
	};

}

