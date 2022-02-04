#include <lexer.h>

int	lex_valid_syntax(char *input)
{
	t_lexer	l;
	t_token	tok;
	t_token	peek;

	l = lex_new(input);
	tok = lex_next_token(&l);
	peek = lex_next_token(&l);
	while (tok.type != END)
	{
		if (tok.type != WORD && tok.type != PIPE && peek.type != WORD)
		{
			printf("minishell: parse error near \'%s\'\n", peek.literal);
			free(tok.literal);
			free(peek.literal);
			return (0);
		}
		free(tok.literal);
		tok = peek;
		peek = lex_next_token(&l);
	}
	free(tok.literal);
	free(peek.literal);
	return (1);
}
