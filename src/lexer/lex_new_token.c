#include <lexer.h>

t_token	lex_new_token(t_type type, char *literal)
{
	t_token	tok;

	tok.type = type;
	tok.literal = literal;
	return (tok);
}
