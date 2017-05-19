#include "stdafx.h"
#include "RigelEditorApp.h"
#include "EditorApp.h"
#include "RigelAPI.h"
namespace RigelCore
{
	RigelEditorApp::RigelEditorApp()
	{
		_app = new EditorApp(this);
		_app->Create();

	}

	RigelEditorApp::~RigelEditorApp()
	{
		DebugLog("~RigelEditorApp");
	}

	void RigelEditorApp::Run()
	{
		_app->Run();
	}

	void RigelEditorApp::onWindowDestroy()
	{
		DebugLog("rigel editor app :: win destroy");

		delete _app;
		_app = 0;
	}		

	void RigelEditorApp::callbackOnGUI()
	{
		delOnGUI();
	}

}
