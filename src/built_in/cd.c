/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:16:53 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/28 14:42:17 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

static void	update_pwd(char **envp)
{
	char	**argv;
	char	*pwd;
	size_t	len;

	pwd = env_expand(g_shell_env.envp, "$PWD");
	len = ft_strlen(pwd);
	free(pwd);
	if (!len)
		return ;
	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("export");
	pwd = getcwd(NULL, 0);
	argv[1] = ft_strjoin("PWD=", pwd);
	export(argv, &envp);
	free(pwd);
	free(argv[0]);
	free(argv[1]);
	free(argv);
}

static void	update_oldpwd(void)
{
	char	**argv;
	char	*oldpwd;
	size_t	len;

	oldpwd = env_expand(g_shell_env.envp, "$OLDPWD");
	len = ft_strlen(oldpwd);
	free(oldpwd);
	if (!len)
		return ;
	argv = ft_calloc(3, sizeof(char *));
	argv[0] = ft_strdup("export");
	oldpwd = env_expand(g_shell_env.envp, "$PWD");
	argv[1] = ft_strjoin("OLDPWD=", oldpwd);
	export(argv, &g_shell_env.envp);
	free(oldpwd);
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
	update_oldpwd();
	update_pwd(envp);
	free(home);
	return (0);
}
