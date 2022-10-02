#pragma once
#include <vector>

namespace rk
{
	template<typename X, typename Y>
	using point = std::pair<X, Y>;

	using point2d = point<double, double>;
}