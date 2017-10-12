#pragma once
#include <functional>
#include <rgcore\rg_windowManager.h>

namespace rg ::rgengine {

	struct RgEngineExternalAdapter;

	//singleton
	class RgEngineWindow {

	public:
		static RgEngineWindow* GetInstance();
		bool Init(const RgEngineExternalAdapter& adapter);
		static RgEngineWindow* Release(RgEngineWindow*);
		
		void EnterRunLoop(std::function<void(void)> onframe);

		rg::RgWindow *  InternalGetWindow();

	private:
		~RgEngineWindow();
		RgEngineWindow();
		void Release();
		RgEngineWindow(const RgEngineWindow&) = delete;
		RgEngineWindow& operator=(RgEngineWindow const&) = delete;

		void OnFrame();

		static RgEngineWindow* m_pInstance;

		rg::RgWindow * m_pRgWindow = nullptr;
		bool m_bEditorMode = false;
		std::function<void(void)> m_funcOnFrame;

	};
}