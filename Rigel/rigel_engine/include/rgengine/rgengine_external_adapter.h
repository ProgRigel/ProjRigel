#pragma once
#include "rgengine_include.h"

namespace rg::rgengine {

	struct RgEngineExternalAdapter {
		bool bEditorMode = false;
		rg::RgGraphicsContext * pGraphicsContext = nullptr;
	};
}