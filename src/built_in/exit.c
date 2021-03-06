/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:24:00 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/23 19:35:26 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

void	free_env(void)
{
	size_t	i;

	i = 0;
	while (g_shell_env.envp[i])
	{
		free(g_shell_env.envp[i]);
		++i;
	}
	free(g_shell_env.envp);
}

int	all_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int	built_in_exit(char **argv)
{
	if (argv && argv[1] && argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	free_env();
	if (argv && printf("exit\n"))
	{
		if (argv[1])
		{
			if (all_digits(argv[1]))
				exit(ft_atoi(argv[1]));
			else
			{
				printf("minishell: exit: %s: "\
				"numeric argument required\n", argv[1]);
				exit(255);
			}
		}
		else
			exit(g_shell_env.last_exit_code);
	}
	else
		exit(g_shell_env.last_exit_code);
	return (0);
}
