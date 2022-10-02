#pragma once
#include <iostream>
#include <string>

#include "Screen.h"

namespace rk
{
	class MainScreen final : public Screen
	{
	public:
		MainScreen(std::unordered_map<std::string_view, std::function<void()>>&& functions, Application* application)
			: Screen(std::move(functions))
		{
			addCommand("cls", std::bind(&MainScreen::clearScreenCommand, this));
			addCommand("rk4", std::bind(&MainScreen::transitionToRK4Command, this));
			addCommand("help", std::bind(&MainScreen::helpCommand, this));
			setApplication(application);
		}

	public:
		void execute() override
		{
			std::cout << "> ";

			std::string input;
			std::getline(std::cin, input);

			if (findCommand(input))
				functions[rk::toLower(input)]();
			else
				std::cout << "[Error]: Invalid command. Type 'help' to check a list of commands.\n\n";
		}

		void mainHeader() override
		{
			CLEAR_SCREEN();
			std::cout << "-= Runge Kutta v1.0 =-\n";
			std::cout << "Made by: Paulo V. C. Galvão\n";
			std::cout << '\n';
			std::cout << "For a list of commands, type 'help'\n\n";
		}

	private:
		void clearScreenCommand()
		{
			CLEAR_SCREEN();
			mainHeader();
		}

		void transitionToRK4Command()
		{
			application->setScreen("rk4_screen");
		}

		void helpCommand()
		{
			std::cout << '\n';

			std::cout << "-= Available Commands =-\n";
			std::cout << "* help\t" << ": Shows this list of commands\n";
			std::cout << "* rk4\t" << ": Enters the Runge Kutta calculator mode\n";
			std::cout << "* quit\t" << ": Finishes the application\n";
			std::cout << "* cls\t" << ": Clears the console screen\n";

			std::cout << '\n';
		}
	};
}