/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:27:36 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/22 23:21:50 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*rm_quotes(char *str)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	char	quote;

	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	quote = 0;
	while ((str)[i])
	{
		if ((str)[i] == quote && ++i)
			quote = 0;
		else if (ft_strchr("'\"", (str)[i]) && !quote && ft_strchr(&str[i + 1], *ft_strchr("'\"", str[i])) && ++i)
			quote = (str)[i - 1];
		else
		{
			tmp[j] = (str)[i];
			++j;
			++i;
		}
	}
	free(str);
	return (tmp);
}
