/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:27:36 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/11 22:57:57 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_quotes(char *str)
{
	char	*tmp;
	char	*new;
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
		else if (ft_strchr("'\"", (str)[i]) && !quote && ++i)
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
