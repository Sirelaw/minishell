#include <lexer.h>

char	lex_peek_char(t_lexer *l)
{
	if (l->read_pos > ft_strlen(l->input))
		return (0);
	else
		return (l->input[l->read_pos]);
}
