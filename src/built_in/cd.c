/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:16:53 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 16:16:53 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

int	cd(char **argv, char **envp)
{
	char	*home;

	home = env_expand(envp, "$HOME");
	if (argv[1] == NULL && *home != '\0')
	{
		if (chdir(home) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else if (argv[2] != NULL)
		return (1);
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}
