/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:28:06 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/06 22:57:13 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wildcard.h>

/**
 * Returns 1 if the next word in str includes a wildcard
**/
int	next_word_has_wildcard(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] && !ft_isspace(str[idx]))
	{
		if (str[idx] == '*')
			return (1);
		++idx;
	}
	return (0);
}

char	*isolate_wildcard(char *str)
{
	size_t	idx;
	char	tmp;
	char	*isolated_wildcard;

	idx = 0;
	while (str[idx] && !ft_isspace(str[idx]))
		++idx;
	tmp = str[idx];
	str[idx] = 0;
	isolated_wildcard = ft_strdup(str);
	str[idx] = tmp;
	return (isolated_wildcard);
}

void	wildcard(char **str)
{
	char	quote;
	size_t	idx;
	char	*wildcard_str;
	t_list	*findings;

	quote = 0;
	idx = 0;
	while ((*str)[idx])
	{
		if ((*str)[idx] == quote)
			quote = 0;
		else if (!quote && ((*str)[idx] == '"' || (*str)[idx] == '\''))
			quote = (*str)[idx];
		while (!quote && ft_isspace((*str)[idx]))
			++idx;
		if (!quote && next_word_has_wildcard(&(*str)[idx]))
		{
			wildcard_str = isolate_wildcard(&(*str)[idx]);
			findings = find_entrys(wildcard_str);
			insert_findings(str, findings);
			free(wildcard_str);
			ft_lstclear(&findings, free);
		}
		++idx;
	}
}
