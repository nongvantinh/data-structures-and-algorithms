#include "Catch2/Catch.hpp"

/*
 Check the validity of '(', ')' in any string
The following rules define a valid string:
- Any left bracket '(' must have a corresponding right parenthesis ')'.
- Any right parenthesis ')' must have a corresponding left parenthesis '('.
Example:
- input = "((abc))"; -> correct
- input = "((abc)"; -> Error
- input = "(abc))"; -> Error
		// case này theo cách em nói đúng ko ?
		))((

*/

/*
Token: '(', 'character-litteral', ')'
The following is the expression grammar:
	Expression:
		Primary
		'(' Expression ')'
	Primary:
		Character-litteral
*/

int expression(const std::string& p_value, int p_index);
int primary(const std::string& p_value, int p_index);

bool is_valid_parenthesis(const std::string& p_value)
{
	try
	{
		return p_value.size() == expression(p_value, 0);
	}
	catch (const std::exception&)
	{
		return false;
	}
}

int expression(const std::string& p_value, int p_index)
{
	// Read and evaluate a primary.
	p_index = primary(p_value, p_index);

	while (p_index != p_value.size())
	{
		// Get the next token from the string.
		char token(p_value[p_index]);
		switch (token)
		{
			// Handles: '(' Expression ')'
		case '(':
		{
			p_index = expression(p_value, ++p_index);
			token = p_value[p_index];
			if (')' != token)
			{
				throw std::runtime_error("')' expected.");
			}
			++p_index;
			continue;
		}
		// Handles: Character-litteral
		default:
			return primary(p_value, p_index);
		}
	}

	return p_index;
}

int primary(const std::string& p_value, int p_index)
{
	while (p_index != p_value.size())
	{
		char token(p_value[p_index]);
		if ('(' != token && token != ')')
			++p_index;
		else
			return p_index;
	}

	return p_index;
}

TEST_CASE("Check validity of parenthesis in string.", "[parenthesis_validity]")
{
	SECTION("No parenthesis.")
	{
		CHECK(true == is_valid_parenthesis("abc"));
	}
	SECTION("Only parenthesis.")
	{
		CHECK(true == is_valid_parenthesis("()"));
	}
	SECTION("parenthesis and character-literal.")
	{
		CHECK(true == is_valid_parenthesis("(abc)"));
	}
	SECTION("Missing ')'")
	{
		CHECK(false == is_valid_parenthesis("(abc"));
	}
	SECTION("Missing '('")
	{
		CHECK(false == is_valid_parenthesis("abc)"));
	}
	SECTION("Input 1: ((abc))")
	{
		CHECK(true == is_valid_parenthesis("((abc))"));
	}
	SECTION("Input 2: ((abc)")
	{
		CHECK(false == is_valid_parenthesis("((abc)"));
	}
	SECTION("Input 3: (abc))")
	{
		CHECK(false == is_valid_parenthesis("(abc))"));
	}
	SECTION("Input 4: ))((")
	{
		CHECK(false == is_valid_parenthesis("))(("));
	}
	SECTION("Input 5: (abc(def))")
	{
		CHECK(true == is_valid_parenthesis("(abc(def))"));
	}
	SECTION("Input 6: (abc(DEF).%$#)")
	{
		CHECK(true == is_valid_parenthesis("(abc(def))"));
	}
}