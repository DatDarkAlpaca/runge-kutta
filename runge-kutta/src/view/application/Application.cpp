#include "Application.h"

void rk::Application::addScreen(std::string_view screenName, Screen* screen)
{
	m_Screens[screenName] = screen;
}

void rk::Application::setScreen(std::string_view screenName)
{
	m_CurrentScreen = m_Screens[screenName];
	m_CurrentScreen->onScreenEnter();
}

void rk::Application::run()
{
	while (true)
		m_CurrentScreen->execute();
}
