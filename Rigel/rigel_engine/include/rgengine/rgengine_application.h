#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>

#include "rgengine_window.h"

namespace rg::rgengine{

	struct RgEngineExternalAdapter;

	class RgEngineApplication {

	private:
		RgEngineApplication(const RgEngineExternalAdapter& adapter);
		~RgEngineApplication();
		RgEngineApplication(const RgEngineApplication&) = delete;
		RgEngineApplication& operator=(const RgEngineApplication&) = delete;
	public:
		static RgEngineApplication * GetInstance();
		static RgEngineApplication * InitEngine(const RgEngineExternalAdapter& adapter);
		static void ReleaseApplication(RgEngineApplication * app);

		void Run();
		void Release();

		void ProcessWndMsg();

	private:
		RgEngineWindow * m_pWindow = nullptr;

	private:
		static RgEngineApplication* m_pApplication;

		std::mutex m_mutexLogic;
		std::condition_variable m_cvLogic;
		std::condition_variable m_cvRender;

		bool m_bToRender = false;
		bool m_bToLogic = false;

		void ThreadLogicProc();

		

		void ProcessRender();
		void ProcessLogic();

	};
}