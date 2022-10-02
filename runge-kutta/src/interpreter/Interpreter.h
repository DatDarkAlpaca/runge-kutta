#pragma once
#include "parser/Parser.h"
#include "Point.h"

namespace rk
{
	double interpret(const function& queue, const point2d& currentPoint);
}