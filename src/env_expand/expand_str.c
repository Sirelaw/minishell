/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:16:46 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/10 19:19:11 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 *	Replaces the characters from start(included) to end(excluded) in src
 *	with a copy of new
*/
static char	*str_replace(char *src, size_t start, size_t end, char *new)
{
	char	*result;

	result = ft_calloc(ft_strlen(src) - (end - start) + ft_strlen(new) + 1, 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, src, start);
	ft_strlcpy(result + start, new, ft_strlen(new) + 1);
	ft_strlcpy(result + start + ft_strlen(new), src + end, ft_strlen(src) - end);
	free(src);
	printf("var inreplace: %s\n", result);
	return (result);
}

static void	expand_var(char **envp, char **str, size_t idx)
{
	size_t	space;
	char	*var;
	char	value;

	space = idx;
	while (!isspace((*str)[space]) && (*str)[space]
		&& (*str)[space] != '"' && (*str)[space] != '\'')
		++space;
	value = (*str)[space];
	(*str)[space] = 0;
	printf("expand_str/expand_var: %s len: %zu\n", &(*str)[idx], ft_strlen(&(*str)[idx])); 
	var = env_expand(envp, &(*str)[idx]);
	(*str)[space] = value;
	*str = str_replace(*str, idx, space, var);
	printf("var: %s\n", *str);
}

/*
 *	Expands all environment variables in *str
 *	given they are not enclosed in single quotes
*/
char	*expand_str(char **envp, char **str)
{
	size_t	idx;
	char	quote;
	size_t	space;
	char	*var;

	idx = 0;
	quote = 0;
	// printf("%s\n", *str);
	while ((*str)[idx])
	{
		if ((*str)[idx] == quote)
			quote = 0;
		else if ((*str)[idx] == '"' && !quote)
			quote = '"';
		else if ((*str)[idx] == '\'' && !quote)
			quote = '\'';
		else if ((*str)[idx] == '$' && quote != '\'')
			expand_var(envp, str, idx);
		++idx;
	}
	return (*str);
}
