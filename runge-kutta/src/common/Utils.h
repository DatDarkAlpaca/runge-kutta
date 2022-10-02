#pragma once
#include <algorithm>
#include <string>

namespace rk
{
	void CLEAR_SCREEN()
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
	}

	std::string toLower(const std::string data)
	{
		std::string copy = data;
		std::transform(copy.begin(), copy.end(), copy.begin(), std::tolower);

		return copy;
	}
}