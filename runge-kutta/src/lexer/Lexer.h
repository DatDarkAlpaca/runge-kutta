#pragma once
#include <vector>
#include <optional>
#include "Token.h"

namespace rk
{
	std::optional<std::vector<Token>> lex(const std::string& input);
}