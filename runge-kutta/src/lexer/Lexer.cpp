#include <optional>
#include "Lexer.h"

namespace
{
	static constexpr char validOperators[] = {
		'\'', '+', '-', '*', '/', '^', '='
	};

	static bool isOperator(char character)
	{
		for (const char& op : validOperators)
		{
			if (character == op)
				return true;
		}

		return false;
	}
}

std::optional<std::vector<rk::Token>> rk::lex(const std::string& input)
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
			return std::nullopt;
	}

	return results;
}
