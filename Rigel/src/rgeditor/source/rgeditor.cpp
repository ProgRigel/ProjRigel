#include "rgeditor.h"
#include <imgui\imgui.h>

#include "rgeditor_core.h"



class RigelEditorApp : public entry::AppI
{
public:
	RigelEditorApp(const char * _name, const char * _description) : entry::AppI(_name, _description) {
	
	}
	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) {
		Args args(_argc, _argv);

		m_width = _width;
		m_height = _height;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
		);

		imguiCreate();


		//rgeditor
		m_pCore = rgeditor::RigelEditorCore::getInstance();
		m_pCore->init();
	}
	int shutdown() {
		m_pCore->shutdown();
		rgeditor::RigelEditorCore::release();

		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}
	bool update() {
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
		{
			imguiBeginFrame(m_mouseState.m_mx
				, m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
			);

			showExampleDialog(this);

			m_pCore->update();


			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);
			bgfx::frame();

			return true;
		}

		return false;
	}

public:


private:
	rgeditor::RigelEditorCore * m_pCore = nullptr;

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

};


extern "C" {
	ENTRY_IMPLEMENT_MAIN(RigelEditorApp, "Rigel", "Editor");
}
