#include "MainScreen.h"

#include "view/application/Application.h"

rk::MainScreen::MainScreen(std::unordered_map<std::string_view, std::function<void()>>&& functions, Application* application)
	: Screen(std::move(functions))
{
	addCommand("cls", std::bind(&MainScreen::clearScreenCommand, this));
	addCommand("rk4", std::bind(&MainScreen::transitionToRK4Command, this));
	addCommand("help", std::bind(&MainScreen::helpCommand, this));
	setApplication(application);
}

void rk::MainScreen::mainHeader()
{
	CLEAR_SCREEN();

	std::cout << "-= Runge Kutta v1.0 =-\n";
	std::cout << "Made by: Paulo V. C. Galvão\n";
	std::cout << '\n';
	std::cout << "For a list of commands, type 'help'\n\n";
}

void rk::MainScreen::clearScreenCommand()
{
	CLEAR_SCREEN();
	mainHeader();
}

void rk::MainScreen::transitionToRK4Command()
{
	application->setScreen("rk4_screen");
}

void rk::MainScreen::helpCommand()
{
	std::cout << '\n';

	std::cout << "-= Available Commands =-\n";
	std::cout << "* help\t" << ": Shows this list of commands\n";
	std::cout << "* rk4\t" << ": Enters the Runge Kutta calculator mode\n";
	std::cout << "* quit\t" << ": Finishes the application\n";
	std::cout << "* cls\t" << ": Clears the console screen\n";

	std::cout << '\n';
}
