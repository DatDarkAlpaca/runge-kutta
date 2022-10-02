#pragma once
#include <unordered_map>
#include <string_view>

#include "view/Screen.h"

namespace rk
{
	class Application
	{
	public:
		explicit Application() = default;

	public:
		void addScreen(std::string_view screenName, Screen* screen);

		void setScreen(std::string_view screenName);

	public:
		void run();

	public:
		std::unordered_map<std::string_view, Screen*> m_Screens;
		Screen* m_CurrentScreen = nullptr;
	};
}