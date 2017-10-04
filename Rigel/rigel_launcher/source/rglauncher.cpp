#include "rglauncher.h"
#include <rgengine\rgengine_application.h>
#include <rgengine\rgengine_external_adapter.h>

int main(){
	rg::rgengine::RgEngineApplication application;

	rg::rgengine::RgEngineExternalAdapter adapter;
	adapter.bEditorMode = false;

	application.Run(adapter);
    return 0;
}