#include <lexer.h>

void	lex_skip_space(t_lexer *l)
{
	while (ft_isspace(l->ch))
		lex_read_char(l);
}

char	*lex_read_word(t_lexer *l)
{
	size_t	start;
	char	quote;

	start = l->pos;
	quote = 0;
	while (l->ch)
	{
		if (l->ch == quote)
			quote = 0;
		else if (l->ch == '"' && !quote)
			quote = '"';
		else if (l->ch == '\'' && !quote)
			quote = '\'';
		if (ft_strchr("<>|& \f\n\r\t\v", lex_peek_char(l)) && !quote)
			break;
		lex_read_char(l);
	}
	return (ft_substr(l->input, start, l->pos + 1 - start));
}

t_token	lex_next_token(t_lexer *l)
{
	t_token	tok;

	lex_skip_space(l);
	if (l->ch == '|')
		tok = lex_new_token(PIPE, ft_strdup("|"));
	else if (l->ch == '<')
	{
		if (lex_peek_char(l) == '<')
		{
			tok = lex_new_token(READ_IN, ft_strdup("<<"));
			lex_read_char(l);
		}
		else
			tok = lex_new_token(RE_IN, ft_strdup("<"));
	}
	else if (l->ch == '>')
	{
		if (lex_peek_char(l) == '>')
		{
			tok = lex_new_token(APPEND, ft_strdup(">>"));
			lex_read_char(l);
		}
		else
			tok = lex_new_token(RE_OUT, ft_strdup(">"));
	}
	else if (!ft_strchr("&|", l->ch))
		tok = lex_new_token(WORD, lex_read_word(l));
	else
		return (lex_new_token(END, ft_strdup("")));
	lex_read_char(l);
	return (tok);
}