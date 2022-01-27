/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:57:54 by sachmull          #+#    #+#             */
/*   Updated: 2021/06/22 16:57:54 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (s == NULL)
		return (NULL);
	sub = (char *)ft_calloc(len + 1, 1);
	if (sub == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (sub);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
