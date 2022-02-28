/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:12 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/28 14:48:13 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

static int	env_remove(char *rm)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (g_shell_env.envp[i])
	{
		if (g_shell_env.envp[j] == rm)
		{
			free(rm);
			++j;
		}
		g_shell_env.envp[i] = g_shell_env.envp[j];
		++i;
		++j;
	}
	return (0);
}

int	unset(char **argv, char ***envp)
{
	size_t	x;
	size_t	y;

	(void)envp;
	x = 0;
	while (argv && argv[x])
	{
		y = 0;
		while (g_shell_env.envp && g_shell_env.envp[y])
		{
			if (ft_strncmp(argv[x], g_shell_env.envp[y], \
				ft_strchr(g_shell_env.envp[y], '=') - g_shell_env.envp[y]) == 0)
				if (env_remove(g_shell_env.envp[y]))
					return (1);
			++y;
		}
		++x;
	}
	return (0);
}
