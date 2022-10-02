#pragma once
#include <iostream>
#include <string>

#include "view/Screen.h"

namespace rk
{
	class MainScreen final : public Screen
	{
	public:
		MainScreen(std::unordered_map<std::string_view, std::function<void()>>&& functions, Application* application);

	public:
		void mainHeader() override;

	private:
		void clearScreenCommand();

		void transitionToRK4Command();

		void helpCommand();
	};
}