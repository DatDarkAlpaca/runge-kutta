#include "Parser.h"

rk::function rk::parse(const std::vector<Token>& tokens)
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
					(operation.rightAssociation && operation.precendece < next.precendece))
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
