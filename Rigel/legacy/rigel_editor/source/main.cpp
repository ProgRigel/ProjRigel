#include "stdafx.h"
#include "app.h"

int main() {
	editor::RigelApp* app = new editor::RigelApp();
	app->Run();
	delete app;

	getchar();
	return 0;
}

