/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:39:45 by sachmull          #+#    #+#             */
/*   Updated: 2021/06/29 16:42:47 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		start_left;
	size_t	counter;
	int		dst_index;
	int		src_index;

	if (dst == NULL && src == NULL)
		return (NULL);
	start_left = 1;
	if (src + len >= dst && src + len <= dst + len)
		start_left = 0;
	counter = 0;
	while (counter < len)
	{
		src_index = counter;
		dst_index = counter;
		if (!start_left)
		{
			src_index = len - counter - 1;
			dst_index = len - counter - 1;
		}
		((char *)dst)[dst_index] = ((char *)src)[src_index];
		counter++;
	}
	return (dst);
}
