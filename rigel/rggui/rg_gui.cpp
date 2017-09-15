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
	void RgGUI::ReleaseAll()
	{
		for (auto pctx : m_vGuiContexts) {
			if (pctx != nullptr) {
				pctx->Release();
				delete pctx;
			}
			pctx = nullptr;
		}
	}
	void RgGUI::Release(RgGUIContext ** pguictx)
	{
		for (auto iter = m_vGuiContexts.begin(); iter != m_vGuiContexts.end(); iter++) {
			if ((*iter) == nullptr) continue;
			if ((*pguictx) == (*iter)) {
				(*pguictx)->Release();
				delete (*pguictx);
				(*iter) = nullptr;
			}
		}
	}
	RgGUI::~RgGUI()
	{
		ReleaseAll();
	}
}

