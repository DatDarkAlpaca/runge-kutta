#pragma once
#include <algorithm>
#include <string>

namespace rk
{
	inline void CLEAR_SCREEN()
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
	}

	inline std::string toLower(const std::string data)
	{
		std::string copy = data;
		std::transform(copy.begin(), copy.end(), copy.begin(), std::tolower);

		return copy;
	}
}