#pragma once
#include <iostream>
#include <string>

#include "Screen.h"

namespace rk
{
	class RKScreen final : public Screen
	{
	public:
		RKScreen(std::unordered_map<std::string_view, std::function<void()>>&& functions, Application* application)
			: Screen(std::move(functions))
		{
			addCommand("cls", std::bind(&RKScreen::clsCommand, this));
			addCommand("back", std::bind(&RKScreen::backCommand, this));
			addCommand("help", std::bind(&RKScreen::helpCommand, this));
			addCommand("calc", std::bind(&RKScreen::calcCommand, this));

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

	private:
		void mainHeader()
		{
			CLEAR_SCREEN();
			std::cout << "-= Runge Kutta RK4 Calculator =-\n";
			std::cout << "According to Wikipedia, the RK4 the most widely known member of the Runge Kutta methods family.\n";
			std::cout << "It is used to solve initial value problems specified as follows:\n\n";

			std::cout << "\ty' = f(x, y) s.t. y(x0) = y0\n\n";

			std::cout << "In order to use this calculator, you'll need to provide:\n";
			std::cout << "\t* The function (f);\n";
			std::cout << "\t* The initial conditions(x0, y0);\n";
			std::cout << "\t* The step size (h);\n";
			std::cout << "\t* The amount of steps (n).\n\n";

			std::cout << "[!] Type 'back' to return to the main screen, and 'help' to see the available operators.\n";
			std::cout << "[!] To begin, type 'calc'\n\n";
		}

	private:
		void clsCommand()
		{
			CLEAR_SCREEN();
			mainHeader();
		}

		void backCommand()
		{
			application->setScreen("main_screen");
		}

		void helpCommand()
		{
			std::cout << '\n';

			std::cout << "-= Available Commands =-\n";
			std::cout << "* help\t" << ": Shows this list of commands\n";
			std::cout << "* calc\t" << ": Performs a RK4 calculation\n";
			std::cout << "* back\t" << ": Switches back to the main menu screen\n";
			std::cout << "* cls\t" << ": Clears the console screen\n";

			std::cout << '\n';
		}

		void calcCommand()
		{
			rk::CLEAR_SCREEN();
			std::cout << "-= Computing RK4 =-\n";

			// Retrieve the function:
			std::vector<rk::Token> tokens;
			do
			{
				std::cout << "Enter the function: ";
				std::string functionInput;
				std::getline(std::cin, functionInput);

				auto tokenResults = rk::lex(functionInput);
				if (tokenResults.has_value())
				{
					tokens = tokenResults.value();
					break;
				}
				else
					std::cout << "Invalid function. Please try again.\n";

			} while (true);

			auto function = rk::parse(tokens);

			// Retrieve the initial conditions:
			rk::point2d initial;
			do
			{
				std::cout << "Enter the initial value of x (x0): ";
				std::string xInput;
				std::getline(std::cin, xInput);

				try
				{
					initial.first = std::stod(xInput);
					break;
				}
				catch (const std::exception& _)
				{
					std::cout << "Invalid value. Please try again.\n";
				}

			} while (true);

			do
			{
				std::cout << "Enter the initial value of y (y0): ";
				std::string xInput;
				std::getline(std::cin, xInput);

				try
				{
					initial.second = std::stod(xInput);
					break;
				}
				catch (const std::exception& _)
				{
					std::cout << "Invalid value. Please try again.\n";
				}

			} while (true);

			// Retrieve the step size:
			double h;
			do
			{
				std::cout << "Enter the step size (h): ";
				std::string hInput;
				std::getline(std::cin, hInput);

				try
				{
					h = std::stod(hInput);
					break;
				}
				catch (const std::exception& _)
				{
					std::cout << "Invalid step size. Please try again.\n";
				}

			} while (true);

			// Retrieve the amount of steps:
			size_t n;
			do
			{
				std::cout << "Enter the amount of steps (n): ";
				std::string nInput;
				std::getline(std::cin, nInput);

				try
				{
					n = std::abs(std::stoi(nInput));
					break;
				}
				catch (const std::exception& _)
				{
					std::cout << "Invalid step size. Please try again.\n";
				}

			} while (true);

			std::cout << "\n-=-= Results Table =-=-\n";
			rk::multiStepRK4(function, initial, h, n);

			std::cout << "\nPress any key to return...";
			std::cin.get();

			clsCommand();
		}
	};
}

