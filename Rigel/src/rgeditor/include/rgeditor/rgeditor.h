#pragma once
#include <rgengine\rgengine.h>
#include <common\common.h>
#include <common\entry\entry.h>
#include <common\bgfx_utils.h>

#include "rgeditor_module.h"

#define RGLOG_DEBUG(x) rgeditor::RgEditorModuleConsole::logDebug(x)

namespace rgeditor {

	class RigelEditorApp : public entry::AppI
	{
	public:
		RigelEditorApp(const char * _name, const char * _description);
		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height);
		int shutdown();
		bool update();

	public:


	private:
		static RigelEditorApp * m_pInstance;

		entry::MouseState m_mouseState;

		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;

	};
}