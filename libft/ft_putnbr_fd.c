/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:57:20 by sachmull          #+#    #+#             */
/*   Updated: 2021/07/15 15:28:46 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	div;
	unsigned int	first_nbr_encountered;
	unsigned int	val;

	div = 1000000000;
	first_nbr_encountered = 0;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	while (div > 0)
	{
		val = n / div;
		if (val != 0 || (val == 0 && first_nbr_encountered))
		{
			val += 48;
			write(fd, &val, 1);
			first_nbr_encountered = 1;
		}
		n -= (n / div) * div;
		div /= 10;
	}
}
