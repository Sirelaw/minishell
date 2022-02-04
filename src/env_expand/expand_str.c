#include <minishell.h>

/*
 *	Replaces the characters from start(included) to end(excluded) in src
 *	with a copy of new
*/
static char	*str_replace(char *src, size_t start, size_t end, char *new)
{
	char	*result;

	result = calloc(strlen(src) - (end - start) + strlen(new) + 1, 1);
	if (!result)
		return (NULL);
	strncpy(result, src, start);
	strncpy(result + start, new, strlen(new));
	strncpy(result + start + strlen(new), src + end, strlen(src) - end);
	return (result);
}

/*
 *	Expands all environment variables in *str
 *	given they are not enclosed in single quotes
*/
void	expand_str(char **envp, char **str)
{
	size_t	idx;
	char	quote;
	size_t	space;
	char	*var;

	idx = 0;
	quote = 0;
	while ((*str)[idx])
	{
		if ((*str)[idx] == quote)
			quote = 0;
		else if ((*str)[idx] == '"' && !quote)
			quote = '"';
		else if ((*str)[idx] == '\'' && !quote)
			quote = '\'';
		else if ((*str)[idx] == '$' && quote != '\'')
		{
			space = idx;
			while (!isspace((*str)[space]) && (*str)[space])
				++space;
			(*str)[space] = 0;
			var = env_expand(envp, &(*str)[idx]);
			(*str)[space] = ' ';
			var = str_replace(*str, idx, space, var);
			free(*str);
			*str = var;
		}
		++idx;
	}
}
