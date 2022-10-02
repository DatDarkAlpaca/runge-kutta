#pragma once
#include <vector>
#include "Token.h"

namespace rk
{
	std::vector<Token> lex(const std::string& input);
}