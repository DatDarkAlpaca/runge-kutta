#include "Interpreter.h"

double rk::interpret(const function& queue, const point2d& currentPoint)
{
	std::deque copy = queue;

	std::vector<double> stack;
	while (!copy.empty())
	{
		Token currentToken = copy.front();
		copy.pop_front();

		switch (currentToken.type)
		{
			case TokenType::NUMBER:
				stack.push_back(std::stod(currentToken.data));
				break;

			case TokenType::X:
				stack.push_back(currentPoint.first);
				break;

			case TokenType::Y:
				stack.push_back(currentPoint.second);
				break;

			case TokenType::OPERATOR:
			{
				double rhs = stack.back();
				stack.pop_back();

				if (stack.empty())
				{
					stack.push_back(-rhs);
					break;
				}

				double lhs = stack.back();
				stack.pop_back();

				switch (currentToken.data[0])
				{
					case '^':
						stack.push_back(pow(lhs, rhs));
						break;

					case '*':
						stack.push_back(lhs * rhs);
						break;

					case '/':
						stack.push_back(lhs / rhs);
						break;

					case '+':
						stack.push_back(lhs + rhs);
						break;

					case '-':
					{
						stack.push_back(lhs - rhs);
						break;
					}

					default:
						throw "Unexpected token";
				}
			}

			break;
		}
	}

	return stack.front();
}
