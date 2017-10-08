#include "rglauncher.h"
#include <rgengine\rgengine_application.h>
#include <rgengine\rgengine_external_adapter.h>

using namespace rg::rgengine;

int main(){

	RgEngineExternalAdapter adapter;
	adapter.bEditorMode = false;

	RgEngineApplication * application = RgEngineApplication::InitEngine(adapter);

	application->Run();

	RgEngineApplication::ReleaseApplication(application);

	getchar();

    return 0;
}