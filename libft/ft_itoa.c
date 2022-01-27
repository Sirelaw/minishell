/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:56:32 by sachmull          #+#    #+#             */
/*   Updated: 2021/06/22 16:56:32 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_of_digits(int val);
static long	power(int base, int power);

char	*ft_itoa(int n)
{
	char	*result;
	long	value;
	size_t	index;
	long	div;

	result = (char *)malloc(nbr_of_digits(n) + 1);
	if (result == NULL)
		return (NULL);
	value = (long)n;
	index = -1;
	div = power(10, nbr_of_digits(n) - 1);
	if (value < 0)
	{
		result[++index] = '-';
		value *= (-1);
		div = power(10, nbr_of_digits(n) - 2);
	}
	while (div >= 1)
	{
		result[++index] = (value / div) + 48;
		value -= (value / div) * div;
		div /= 10;
	}
	result[++index] = '\0';
	return (result);
}

static long	power(int base, int power)
{
	long	result;
	int		counter;

	result = 1;
	counter = 0;
	while (counter < power)
	{
		result *= (long)base;
		counter++;
	}
	return (result);
}

/**
 * Returns the number of fields the given value has e.g. 15 -> 2; -42 -> 3
 * A minus sign takes an extra field
**/

static int	nbr_of_digits(int val)
{
	int	digits;

	digits = 0;
	if (val < 0)
		digits++;
	while (val / 10)
	{
		digits++;
		val /= 10;
	}
	digits++;
	return (digits);
}
