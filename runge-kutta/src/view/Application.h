#pragma once
#include "Screen.h"

namespace rk
{
	class Application
	{
	public:
		explicit Application() = default;

	public:
		void addScreen(std::string_view screenName, Screen* screen)
		{
			m_Screens[screenName] = screen;
		}

		void setScreen(std::string_view screenName)
		{
			m_CurrentScreen = m_Screens[screenName];
			m_CurrentScreen->onScreenEnter();
		}

	public:
		void run()
		{
			while (true)
				m_CurrentScreen->execute();
		}

	public:
		std::unordered_map<std::string_view, Screen*> m_Screens;
		Screen* m_CurrentScreen = nullptr;
	};
}