#include "rgengine_window.h"
#include "rgengine_external_adapter.h"

namespace rg::rgengine {
	RgEngineWindow* RgEngineWindow::m_pInstance = nullptr;
	RgEngineWindow * RgEngineWindow::GetInstance()
	{
		if (m_pInstance == nullptr) {
			m_pInstance = new RgEngineWindow();
		}
		return m_pInstance;
	}
	bool RgEngineWindow::Init(const RgEngineExternalAdapter & adapter)
	{
		if (adapter.bEditorMode) {
			return false;
		}
		else
		{
			RgWindowSettings settings;
			HRESULT result = RgWindowManager::createWindow(&m_pRgWindow, &settings);
			if (result != S_OK) return false;

			auto& mgr = RgWindowManager::getInstance();
			mgr.registerWindow(m_pRgWindow);
			m_pRgWindow->showWindow();


			return true;
		}
	}
	void RgEngineWindow::Release()
	{
		auto& mgr = RgWindowManager::getInstance();
		mgr.releaseWindow();
		m_pRgWindow = nullptr;
	}
	RgEngineWindow::~RgEngineWindow()
	{
		Release();
		m_pInstance = nullptr;
	}
	void RgEngineWindow::EnterRunLoop(std::function<void(void)> onframe)
	{
		m_funcOnFrame = onframe;

		m_pRgWindow->EventOnFrame.connect<RgEngineWindow, &RgEngineWindow::OnFrame>(this);
		auto& mgr = RgWindowManager::getInstance();
		mgr.enterMainLoop();
	}
	RgEngineWindow::RgEngineWindow()
	{
	}
	void RgEngineWindow::OnFrame()
	{
		m_funcOnFrame();
	}
}


