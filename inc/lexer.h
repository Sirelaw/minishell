#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
# include <stdlib.h>
# include <libft.h>

typedef enum e_type {	PIPE,
						RE_IN,
						RE_OUT,
						APPEND,
						READ_IN,
						WORD,
						END} t_type;

typedef struct s_token
{
	t_type	type;
	char	*literal;
}				t_token;

typedef struct s_lexer
{
	char	*input;
	size_t	pos;
	size_t	read_pos;
	char	ch;
}				t_lexer;

t_lexer	lex_new(char *input);
void	lex_read_char(t_lexer *l);
t_token	lex_next_token(t_lexer *l);
t_token	lex_new_token(t_type type, char *literal);
char	lex_peek_char(t_lexer *l);
int		lex_valid_syntax(char *input);

#endif
