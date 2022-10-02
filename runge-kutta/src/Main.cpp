#include "view/Application.h"
#include "view/MainScreen.h"
#include "view/RK4Screen.h"

namespace
{
	inline void exitCommand()
	{
		exit(0);
	}

	inline std::unordered_map<std::string_view, std::function<void()>> defaultFunctionMap = {
		{ "cls", rk::CLEAR_SCREEN },
		{ "quit", exitCommand }
	};
}

int main()
{	
	std::setlocale(LC_ALL, "");
	using namespace rk;

	Application application;
	application.addScreen("rk4_screen", new RKScreen(std::move(defaultFunctionMap), &application));
	application.addScreen("main_screen", new MainScreen(std::move(defaultFunctionMap), &application));

	application.setScreen("main_screen");
	application.run();
}