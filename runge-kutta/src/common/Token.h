#pragma once
#include <string>

namespace rk
{
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
}
