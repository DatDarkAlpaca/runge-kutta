#pragma once
#include <deque>
#include <vector>
#include "common/Token.h"

namespace rk
{
	using function = std::deque<Token>;

	function parse(const std::vector<Token>& tokens);
}