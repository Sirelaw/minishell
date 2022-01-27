/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:19:06 by sachmull          #+#    #+#             */
/*   Updated: 2021/07/05 18:30:20 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	null;
	size_t	index;

	null = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (dst[null] != '\0' && null < size)
		null++;
	if (null == size)
		return (null + ft_strlen(src));
	index = 0;
	while (src[index] != '\0' && null + index + 1 < size)
	{
		dst[null + index] = src[index];
		index++;
	}
	if (size > 0)
		dst[null + index] = '\0';
	return (ft_strlen(dst) + ft_strlen(&(src[index])));
}
