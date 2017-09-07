#include "app.h"

int main() {
	RigelApp* app = new RigelApp();
	app->Run();
	delete app;

	getchar();
	return 0;
}

