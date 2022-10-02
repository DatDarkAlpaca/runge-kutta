#pragma once
#include <vector>
#include <optional>
#include "common/Token.h"

namespace rk
{
	std::optional<std::vector<Token>> lex(const std::string& input);
}