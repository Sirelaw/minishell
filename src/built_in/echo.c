/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:16:57 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/10 18:53:24 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

int	echo(char **argv)
{
	size_t	idx;

	idx = 1;
	if (argv[1] == NULL)
		return (0);
	if (ft_strncmp("-n", argv[1], 3) == 0)
		idx = 2;
	while (argv[idx])
	{
		printf("%s", argv[idx]);
		if (argv[idx + 1])
			printf(" ");
		++idx;
	}
	if (ft_strncmp("-n", argv[1], 3) != 0)
		printf("\n");
	return (0);
}
