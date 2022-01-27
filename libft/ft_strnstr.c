/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:57:38 by sachmull          #+#    #+#             */
/*   Updated: 2021/06/22 16:57:38 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	index;
	char	segfault;

	if (little == NULL)
		segfault = little[0];
	if (big == NULL)
		segfault = big[0];
	little_len = ft_strlen((char *)little);
	index = 0;
	if (little_len == 0)
		return ((char *)big);
	if (little_len > len)
		return (NULL);
	while (index <= len - little_len)
	{
		if (ft_strncmp(big + index, little, little_len) == 0)
			return ((char *)big + index);
		index++;
	}
	return (NULL);
}
