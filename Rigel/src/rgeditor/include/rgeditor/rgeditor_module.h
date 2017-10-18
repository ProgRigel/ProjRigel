#pragma once
#include "rgeditor.h"
#include <vector>
#include <map>
#include <deque>
#include <list>
#include <cstdarg>
#include <iostream>
#include <sstream>
namespace rgeditor {

	class RgEditorModule;
	class RgEditorModuleModuleManager;
	class RgEditorModuleConsole;

	enum class RgEditorBaseModuleType
	{
		EGUI = 0,
		ModuleManager = 1,
		Console = 2,
	};

	void rgEditorModuleInit();
	void rgEditorModuleShutdown();
	void rgEditorModuleUpdate();

	class RgEditorModule {

	public:
		RgEditorModule(RgEditorBaseModuleType);
		virtual void init() = 0;
		virtual void shutdown() = 0;
		virtual void update();

	private:
		RgEditorModule(const RgEditorModule&) = delete;
		RgEditorModule& operator=(const RgEditorModule&) = delete;

		const char * m_name;
		RgEditorBaseModuleType m_type;
	};


	///////////////////////////////////////
#pragma region BasicModule

	class RgEditorModuleModuleManager : public RgEditorModule {

	public:
		RgEditorModuleModuleManager():RgEditorModule(RgEditorBaseModuleType::ModuleManager){}
		void init();
		void shutdown();
	};


	class RgEditorModuleConsole :public RgEditorModule {
	public:
		RgEditorModuleConsole() :RgEditorModule(RgEditorBaseModuleType::Console) {
			m_pInstance = this;
		}
		void init();
		void shutdown();

		static void logDebug(const char * msg);

	private:
		void drawLogs();
		void drawMenubar();

		static RgEditorModuleConsole* m_pInstance;
		std::deque<std::string> m_logdeque;
	};
#pragma endregion
	///////////////////////////////////////


}