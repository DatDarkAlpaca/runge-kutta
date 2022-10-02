#pragma once
#include <unordered_map>
#include <functional>
#include <iostream>

#include "common/Utils.h"

namespace rk
{
	class Application;

	class Screen
	{
	public:
		explicit Screen(std::unordered_map<std::string_view, std::function<void()>>&& functions) noexcept
			: functions(functions) { }

		virtual ~Screen() = default;

	public:
		virtual void execute() 
		{
			std::cout << "> ";

			std::string input;
			std::getline(std::cin, input);

			if (findCommand(input))
				functions[rk::toLower(input)]();
			else
				std::cout << "[Error]: Invalid command. Type 'help' to check a list of commands.\n\n";
		}

		virtual void mainHeader() { }

		virtual void onScreenEnter() { mainHeader(); }

	protected:
		bool findCommand(const std::string& command) const
		{
			return functions.find(toLower(command)) != functions.end();
		}

		void addCommand(std::string_view command, const std::function<void()>& function)
		{
			functions[command] = function;
		}

	protected:
		void setApplication(Application* application) { this->application = application; }

	protected:
		std::unordered_map<std::string_view, std::function<void()>> functions;
		Application* application = nullptr;
	};
}