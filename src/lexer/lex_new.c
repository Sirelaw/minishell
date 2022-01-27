#include <lexer.h>

t_lexer	lex_new(char *input)
{
	t_lexer	l;

	l.input = input;
	l.pos = 0;
	l.read_pos = 1;
	l.ch = input[0];
	return (l);
}
