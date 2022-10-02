#pragma once
#include <unordered_map>
#include <functional>

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
		virtual void execute() { }

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