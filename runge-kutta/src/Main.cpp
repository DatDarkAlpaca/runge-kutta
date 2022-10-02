#include <string_view>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <deque>
#include <stack>

#define DEBUG

// Token:
enum class TokenType
{
	NONE = -1,
	NUMBER,
	OPERATOR,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	X,
	Y
};

struct Token
{
	TokenType type;
	std::string data;
	int precendece = -1;
	bool rightAssociation = false;
};

// Lexer:
namespace
{
	inline constexpr char validOperators[] = {
		'\'', '+', '-', '*', '/', '^', '='
	};

	bool isOperator(char character)
	{
		for (const char& op : validOperators)
		{
			if (character == op)
				return true;
		}

		return false;
	}
}

std::vector<Token> lex(const std::string& input)
{
	const char* current = input.c_str();

	std::vector<Token> results;

	while (true)
	{
		if (std::isspace(*current))
		{
			++current;
			continue;
		}

		else if (*current == '\0')
			break;

		else if (std::isdigit(*current))
		{
			const char* begin = current;

			size_t amountDot = 0;
			while (std::isdigit(*current) || *current == '.')
			{
				if (amountDot > 1)
					throw "Invalid number";

				if (*current == '.')
					++amountDot;

				++current;
			}

			std::string data(begin, current - begin);
			results.push_back({ TokenType::NUMBER, data });
		}

		else if (isOperator(*current))
		{
			int precedence = -1;
			bool rightAssociation = false;
			switch (*current)
			{
				case '^':
					precedence = 4; 
					rightAssociation = true;
					break;
				case '*':
					precedence = 3; 
					break;
				case '/':
					precedence = 3; 
					break;
				case '+':
					precedence = 2; 
					break;
				case '-':
					precedence = 2; 
					break;
			}

			results.push_back({ TokenType::OPERATOR, std::string(1, *current), precedence, rightAssociation });
			++current;
		}

		else if (*current == '(')
		{
			results.push_back({ TokenType::LEFT_PARENTHESIS, "(" });
			++current;
		}

		else if (*current == ')')
		{
			results.push_back({ TokenType::RIGHT_PARENTHESIS, ")" });
			++current;
		}

		else if (std::tolower(*current) == 'x')
		{
			results.push_back({ TokenType::X, "x" });
			++current;
		}

		else if (std::tolower(*current) == 'y')
		{
			results.push_back({ TokenType::X, "y" });
			++current;
		}

		else
			throw "Invalid operator";
	}

	return results;
}

// Shutting-Yard Parser:
namespace
{
	using function = std::deque<Token>;
}

function parse(const std::vector<Token>& tokens)
{
	std::deque<Token> resultFunction;
	std::vector<Token> stack;

	for (const auto& token : tokens) 
	{
		switch (token.type)
		{
			case TokenType::NONE:
				break;

			case TokenType::NUMBER:
			case TokenType::X:
			case TokenType::Y:
				resultFunction.push_back(token);
				break;

			case TokenType::OPERATOR:
			{
				Token operation = token;

				while (!stack.empty())
				{
					Token next = stack.back();

					if ((!operation.rightAssociation && operation.precendece <= next.precendece) ||
						( operation.rightAssociation && operation.precendece <  next.precendece))
					{
						stack.pop_back();
						resultFunction.push_back(next);
						continue;
					}

					break;
				}
				
				stack.push_back(operation);
				break;
			}

			case TokenType::LEFT_PARENTHESIS:
				stack.push_back(token);
				break;

			case TokenType::RIGHT_PARENTHESIS:
			{
				bool parenthesisMatch = false;

				while (!stack.empty() && stack.back().type != TokenType::LEFT_PARENTHESIS) 
				{
					resultFunction.push_back(stack.back());
					stack.pop_back();
					parenthesisMatch = true;
				}

				stack.pop_back();

				if (!parenthesisMatch && stack.empty())
					throw "Unmatched right parenthesis";

				break;
			}

			default:
				throw "Unexpected token";
		}
	}

	while (!stack.empty()) 
	{
		if (stack.back().type == TokenType::LEFT_PARENTHESIS) 
		{
			throw "Unmatched left parenthesis";
			return {};
		}

		resultFunction.push_back(std::move(stack.back()));
		stack.pop_back();
	}

	return resultFunction;
}

// Expression Interpreter:
namespace
{
	template<typename X, typename Y>
	using point = std::pair<X, Y>;

	using point2d = point<double, double>;
}

double interpret(const function& queue, const point2d& currentPoint)
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
						stack.push_back(lhs - rhs);
						break;

					default:
						throw "Unexpected token";
				}
			}
			break;
		}
	}

	return stack.front();
}

// Runge Kutta:
point2d singleStepRungeKutta(const function& func, const point2d init, double h)
{
	double k1 = h * interpret(func, init);
	double k2 = h * interpret(func, { init.first + h / 2, init.second + k1 / 2 });
	double k3 = h * interpret(func, { init.first + h / 2, init.second + k2 / 2 });
	double k4 = h * interpret(func, { init.first + h, init.second + k3 });
	double k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;

	return point2d(init.first + h, init.second + k);
}

// Debug:
void debugLexerResults(const std::vector<Token>& deqeue)
{
	std::cout << "[Debug] Tokens Lexed: ";
	for (const auto& token : deqeue)
		std::cout << token.data << ' ';

	std::cout << '\n';
}

void debugParseResults(const std::deque<Token>& deqeue)
{
	std::cout << "[Debug] Parse Results: ";
	for (const auto& token : deqeue)
		std::cout << token.data << ' ';

	std::cout << '\n';
}

int test()
{
	std::cout << "Enter the function: ";
	std::string input;
	std::getline(std::cin, input);

	auto tokens = lex(input);

#ifdef DEBUG
	debugLexerResults(tokens);
#endif // TOKEN DEBUG

	auto fun = parse(tokens);

#ifdef DEBUG
	debugParseResults(fun);
#endif // QUEUE DEBUG

	auto result = singleStepRungeKutta(fun, { 0, 0 }, 0.1);
	std::cout << "Results: " << result.first << ' ' << result.second << '\n';

	return 0;
}