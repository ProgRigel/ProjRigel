#pragma once
#include <string>

namespace rgeditor {

	struct RigelProject {
		std::wstring proj_path;
		std::string proj_name;
		bool tempProj = true;
		bool valid = false;
	};

	class RigelEditorCore {
	public:
		static RigelEditorCore * getInstance();
		static void release();

		static void showEntryPage();

		void projectNew(bool _tempProj = false);
		void projectOpen();
		void projectDirty();

		void guiBasis();
		void guiMainMenuBar();
		void guiEnteryPage();
		void guiProjectInfo();

		void init();
		void shutdown();
		void update();


	private:
		RigelEditorCore() = default;
		~RigelEditorCore();
		RigelEditorCore(const RigelEditorCore&) = delete;
		RigelEditorCore& operator=(const RigelEditorCore&) = delete;

		static RigelEditorCore * m_pInstance;

		bool m_bShowEntryPage = true;

		RigelProject m_currentProj;
	};


}