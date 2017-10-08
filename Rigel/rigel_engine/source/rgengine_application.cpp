#include "rgengine_include.h"
#include "rgengine_application.h"

using namespace std;

namespace rg::rgengine{

	RgEngineApplication* RgEngineApplication::m_pApplication = nullptr;


	RgEngineApplication::RgEngineApplication(const RgEngineExternalAdapter & adapter)
	{
	}

	RgEngineApplication * RgEngineApplication::GetInstance()
	{
		return m_pApplication;
		return nullptr;
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
	}


	void RgEngineApplication::Run()
	{
		std::thread threadLogic(&RgEngineApplication::ThreadLogicProc, &(*this));

		m_bToRender = true;

		auto time_p = std::chrono::system_clock::now();

		while (true)
		{
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

		threadLogic.join();
	}

	void RgEngineApplication::Release()
	{
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

	void RgEngineApplication::ProcessRender()
	{
		//printf("render\n");
	}

	void RgEngineApplication::ProcessLogic()
	{
		//printf("logic\n");
	}



}