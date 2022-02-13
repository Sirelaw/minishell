/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:24:00 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/13 18:41:57 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

int	built_in_exit(char **argv)
{
	printf("exit\n");
	if (argv[1])
	{
		if (argv[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		exit(ft_atoi(argv[1]));
	}
	else
		exit(g_shell_env.last_exit_code);
	return (0);
}
