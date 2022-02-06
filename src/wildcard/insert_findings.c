/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_findings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:40:44 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/06 23:04:32 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wildcard.h>

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
	ft_strlcpy(result + start, new, ft_strlen(new));
	ft_strlcpy(result + start + ft_strlen(new), src + end, ft_strlen(src) - end);
	free(src);
	return (result);
}

char	*combine_findings(t_list *findings)
{
	char	*combination;
	char	*tmp;

	combination = ft_calloc(1, 1);
	while (findings)
	{
		tmp = ft_strjoin(combination, findings->content);
		free(combination);
		combination = tmp;
		if (findings->next)
		{
			tmp = ft_strjoin(combination, " ");
			free(combination);
			combination = tmp;
		}
		findings = findings->next;
	}
	return (combination);
}

void	insert_findings(char **str, t_list *findings)
{
	char	*to_insert;
	size_t	space;

	to_insert = combine_findings(findings);
	while (!ft_isspace(*str[space]))
		++space;
	*str = str_replace(*str, 0, space, to_insert);
	free(to_insert);
}
