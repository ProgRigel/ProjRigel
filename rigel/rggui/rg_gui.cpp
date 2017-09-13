#include "rggui.h"

#include "rg_gui.h"
#include "rg_gui_context.h"

namespace rg {

	std::vector<RgGUIContext*> RgGUI::m_vGuiContexts;

	bool RgGUI::CreateRgGUIContext(RgGUIContext ** pguictx)
	{
		RgGUIContext* guictx = new RgGUIContext();
		(*pguictx) = guictx;

		m_vGuiContexts.push_back(guictx);

		return true;
	}
	void RgGUI::Release()
	{
		for each (auto pctx in m_vGuiContexts)
		{
			if (pctx != nullptr) {
				pctx->Release();
				delete pctx;
			}
			pctx = nullptr;
		}
	}
	RgGUI::~RgGUI()
	{
	}
}

