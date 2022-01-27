/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:56:50 by sachmull          #+#    #+#             */
/*   Updated: 2021/06/22 16:56:50 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbr_of_ptrs(char *str, char c);

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	start;
	size_t	end;
	size_t	idx;

	split = malloc(nbr_of_ptrs((char*)s, c) * sizeof(char *));
	start = 0;
	end = 0;
	idx = 0;
	while (s[end] != '\0')
	{
		while (s[start] == c && s[start])
			++start;
		end = start;
		while (s[end] != c && s[end])
			++end;
		if (start == end)
			break;
		split[idx] = ft_substr(s, start, end - start);
		++idx;
		start = end;
	}
	split[idx] = NULL;
	return (split);
}

static size_t	nbr_of_ptrs(char *str, char c)
{
	size_t		idx;
	size_t		counter;
	char		*set;

	set = ft_calloc(2, 1);
	set[0] = c;
	idx = 0;
	counter = 0;
	str = ft_strtrim(str, set);
	while (str[idx])
	{
		++counter;
		while (str[idx] != c && str[idx])
			++idx;
		while (str[idx] == c && str[idx])
			++idx;
	}
	free(str);
	free(set);
	return (counter + 1);
}
