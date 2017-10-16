#pragma once
#include "rgeditor.h"
#include <vector>
#include <map>
#include <queue>
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
		RgEditorModuleConsole() :RgEditorModule(RgEditorBaseModuleType::Console) {}
		void init();
		void shutdown();

	private:
		void drawLogs();
	};
#pragma endregion
	///////////////////////////////////////


}