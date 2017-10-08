#include "rgengine_include.h"
#include "rgengine_application.h"
#include <functional>

using namespace std;

namespace rg::rgengine{

	RgEngineApplication* RgEngineApplication::m_pApplication = nullptr;


	RgEngineApplication::RgEngineApplication(const RgEngineExternalAdapter & adapter)
	{

		m_pWindow = RgEngineWindow::GetInstance();
		m_pWindow->Init(adapter);
	}


	void RgEngineApplication::Release()
	{
		if (m_pWindow != nullptr) { delete m_pWindow; m_pWindow = nullptr; }
	}

	RgEngineApplication * RgEngineApplication::GetInstance()
	{
		return m_pApplication;
	}

	RgEngineApplication * RgEngineApplication::InitEngine(const RgEngineExternalAdapter & adapter)
	{
		if (m_pApplication == nullptr) {
			m_pApplication = new RgEngineApplication(adapter);
		}

		return m_pApplication;
	}

	void RgEngineApplication::ReleaseApplication(RgEngineApplication * app)
	{
		if (app != nullptr) {
			app->Release();
			delete app;
		}
	}

	RgEngineApplication::~RgEngineApplication()
	{
		Release();
	}


	void RgEngineApplication::Run()
	{
		//setup logic thread
		std::thread threadLogic(&RgEngineApplication::ThreadLogicProc, &(*this));
		m_bToRender = true;

		//enter render runloop
		m_pWindow->EnterRunLoop([this]() { this->ProcessWndMsg(); });

		//wait logic thread
		threadLogic.join();
		RgLogD() << "thread:logic end";
	}


	void RgEngineApplication::ThreadLogicProc()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lk(m_mutexLogic);
			m_cvLogic.wait(lk, [this]() {return m_bToLogic; });
			m_bToLogic = false;
			m_bToRender = true;
			lk.unlock();
			m_cvRender.notify_one();

			ProcessLogic();
		}
		
	}

	void RgEngineApplication::ProcessWndMsg()
	{
		static auto time_p = std::chrono::system_clock::now();

		auto time_elapsed = std::chrono::system_clock::now() - time_p;

		if (time_elapsed > std::chrono::milliseconds(30)) {
			std::unique_lock<std::mutex> lk(m_mutexLogic);
			m_cvRender.wait(lk, [this]() { return m_bToRender; });
			m_bToRender = false;
			m_bToLogic = true;
			lk.unlock();
			m_cvLogic.notify_one();
			ProcessRender();

			time_p = std::chrono::system_clock::now();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}

	void RgEngineApplication::ProcessRender()
	{

	}

	void RgEngineApplication::ProcessLogic()
	{

	}



}