#pragma once
#include <iostream>
#include <string>

#include "view/Screen.h"

namespace rk
{
	class RKScreen final : public Screen
	{
	public:
		RKScreen(std::unordered_map<std::string_view, std::function<void()>>&& functions, Application* application);

	public:
		void mainHeader() override;

	private:
		void clsCommand();

		void backCommand();

		void helpCommand();

		void calcCommand();
	};
}

