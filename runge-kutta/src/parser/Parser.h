#pragma once
#include <deque>
#include <vector>
#include "Token.h"

namespace rk
{
	using function = std::deque<Token>;

	function parse(const std::vector<Token>& tokens);
}