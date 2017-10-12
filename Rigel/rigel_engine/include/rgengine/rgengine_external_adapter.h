#pragma once
#include "rgengine_include.h"

namespace rg::rgengine {

	struct RgEngineExternalAdapter {
		bool bEditorMode = false;
		RgGraphicsContext * pGraphicsContext = nullptr;
		RgWindow * pWindow = nullptr;
	};
}