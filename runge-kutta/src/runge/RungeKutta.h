#pragma once
#include <iostream>

#include "interpreter/Interpreter.h"
#include "parser/Parser.h"
#include "Point.h"

namespace rk
{
	inline point2d rungeKuttaRK4(const function& func, const point2d init, double h)
	{
		double k1 = h * interpret(func, init);
		double k2 = h * interpret(func, { init.first + h / 2, init.second + k1 / 2 });
		double k3 = h * interpret(func, { init.first + h / 2, init.second + k2 / 2 });
		double k4 = h * interpret(func, { init.first + h, init.second + k3 });
		double k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		return point2d(init.first + h, init.second + k);
	}

	inline void multiStepRK4(const function& func, point2d init, double h, size_t steps)
	{
		size_t index = 0;
		while (steps--)
		{
			auto result = rungeKuttaRK4(func, init, h);
			std::cout << index << ": " << "(" << result.first << ", " << result.second << ")\n";
			init = result;
			++index;
		}
	}
}