#pragma once
#include <iostream>
#include <vector>
#include <deque>

#include "Token.h"

namespace rk
{
	inline void debugLexerResults(const std::vector<Token>& deqeue)
	{
		std::cout << "[Debug] Tokens Lexed: ";
		for (const auto& token : deqeue)
			std::cout << token.data << ' ';

		std::cout << '\n';
	}

	inline void debugParseResults(const std::deque<Token>& deqeue)
	{
		std::cout << "[Debug] Parse Results: ";
		for (const auto& token : deqeue)
			std::cout << token.data << ' ';

		std::cout << '\n';
	}
}