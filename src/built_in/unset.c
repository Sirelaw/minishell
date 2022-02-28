/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:12 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/25 14:51:41 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>
/*
static int	env_add(char ***env, char *var)
{
	size_t	idx;
	char	**new;

	idx = 0;
	while ((*env) && (*env)[idx])
		++idx;
	new = ft_calloc(idx + 2, sizeof(char *));
	if (!new)
		return (1);
	idx = 0;
	while ((*env) && (*env)[idx])
	{
		new[idx] = (*env)[idx];
		++idx;
	}
	new[idx] = var;
	free(*env);
	*env = new;
	return (0);
}
*/
// static int	env_remove(char ***env, char *var)
// {
// 	size_t	idx;
// 	size_t	idx2;
// 	char	**new;

// 	idx = 0;
// 	while ((*env) && (*env)[idx])
// 		++idx;
// 	new = ft_calloc(idx, sizeof(char *));
// 	if (!new)
// 		return (1);
// 	idx = 0;
// 	/*
// 	while ((*env) && (*env)[idx])
// 	{
// 		if ((*env)[idx] != var)
// 			if (env_add(&new, (*env)[idx]))
// 				return (1);
// 		++idx;
// 	}
// 	*/
// 	idx2 = 0;
// 	while (*env && (*env)[idx])
// 	{
// 		if ((*env)[idx] != var)
// 		{
// 			new[idx2] = (*env)[idx];
// 			++idx2;
// 		}
// 		++idx;
// 	}
// 	free(var);
// 	free(*env);
// 	printf("This is fine\n");
// 	*env = new;
// 	printf("This is still fine\n");
// 	return (0);
// }

// int	unset(char **argv, char ***envp)
// {
// 	size_t	x;
// 	size_t	y;

// 	x = 0;
// 	while (argv && argv[x])
// 	{
// 		y = 0;
// 		while ((*envp) && (*envp)[y])
// 		{
// 			if (ft_strncmp(argv[x], (*envp)[y], \
// 				ft_strchr((*envp)[y], '=') - (*envp)[y]) == 0)
// 				if (env_remove(envp, (*envp)[y]))
// 					return (1);
// 			++y;
// 		}
// 		++x;
// 	}
// 	return (0);
// }

static int	env_remove(char *var)
{
	size_t	idx;
	size_t	idx2;
	char	**new;

	idx = 0;
	while (g_shell_env.envp && g_shell_env.envp[idx])
		++idx;
	new = ft_calloc(idx, sizeof(char *));
	if (!new)
		return (1);
	idx = 0;
	idx2 = 0;
	while (g_shell_env.envp && g_shell_env.envp[idx])
	{
		if (g_shell_env.envp[idx] != var)
		{
			printf("This is fine\n");
			new[idx2] = g_shell_env.envp[idx];
			printf("This is still fine\n");
			++idx2;
		}
		++idx;
	}
	free(var);
	free(g_shell_env.envp);
	printf("%s\n", new[3]);
	g_shell_env.envp = new;
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
	printf("FINE\n");
	return (0);
}
