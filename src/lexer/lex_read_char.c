#include <lexer.h>

void	lex_read_char(t_lexer *l)
{
	if (l->read_pos > ft_strlen(l->input))
		l->ch = 0;
	else
		l->ch = l->input[l->read_pos];
	l->pos = l->read_pos;
	++l->read_pos;
}
