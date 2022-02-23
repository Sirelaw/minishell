/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:16:53 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/23 18:29:37 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

static void	update_cwd(char **envp)
{
	char	**argv;
	char	*cwd;

	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("export");
	cwd = getcwd(NULL, 0);
	argv[1] = ft_strjoin("PWD=", cwd);
	export(argv, &envp);
	free(cwd);
	free(argv[0]);
	free(argv[1]);
	free(argv);
}

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
	update_cwd(envp);
	free(home);
	return (0);
}
