/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:01 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/28 16:25:22 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

int	env(char **envp)
{
	size_t	idx;

	(void)envp;
	idx = 0;
	while (g_shell_env.envp[idx])
	{
		printf("%s\n", g_shell_env.envp[idx]);
		++idx;
	}
	return (0);
}
