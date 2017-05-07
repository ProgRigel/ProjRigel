#include "stdafx.h"
#include "RigelEditorApp.h"
#include "cRigelEditorApp.h"

namespace RigelCore
{
	RigelEditorApp::RigelEditorApp()
	{
		_app = new cRigelEditorApp(this);
		_app->Create();
	}

	RigelEditorApp::~RigelEditorApp()
	{
		std::cout << "~RigelEditorApp" << std::endl;
	}

	void RigelEditorApp::Run()
	{
		_app->Run();
	}

	void RigelEditorApp::onWindowDestroy()
	{
		std::cout << "rigel editor app :: win destroy" << std::endl;

		delete _app;
		_app = 0;
	}

	void RigelEditorApp::callbackOnGUI()
	{
		delOnGUI();
	}

}
