#pragma once
#include "Point.h"

#include "parser/Parser.h"
#include "interpreter/Interpreter.h"

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
}