/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:19:17 by sachmull          #+#    #+#             */
/*   Updated: 2021/07/05 19:10:57 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;

	start = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, *start) && *start != '\0')
		++start;
	if (*start == '\0')
		return (ft_substr(start, 0, 0));
	while (ft_strchr(set, *end))
		--end;
	return (ft_substr(start, 0, end - start + 1));
}
