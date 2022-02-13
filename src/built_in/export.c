/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:05 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/13 21:52:29 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

size_t	get_len(char **env)
{
	size_t	len;

	len = 0;
	while (env[len])
		++len;
	return (len);
}

void	print(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		printf("%s\n", env[i]);
		++i;
	}
}

void	print_env(char **argv, char **env)
{
	size_t	i;
	char	*tmp;
	size_t	len;

	if (argv[1])
		return ;
	len = get_len(env);
	while (len)
	{
		i = 0;
		while (i < len - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
			++i;
		}
		--len;
	}
	print(env);
	free(env);
}

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
	*env = new;
	return (0);
}

int	export(char **argv, char ***envp)
{
	size_t	x;
	size_t	y;

	x = 0;
	print_env(argv, dup_envp(*envp));
	while (argv[x])
	{
		y = 0;
		while (ft_strchr(argv[x], '=') && (*envp) && (*envp)[y])
		{
			if (ft_strncmp(argv[x], (*envp)[y], ft_strchr((*envp)[y], '=') \
				- (*envp)[y]) == 0)
			{
				free((*envp)[y]);
				(*envp)[y] = ft_strdup(argv[x]);
				break ;
			}
			++y;
		}
		if (ft_strchr(argv[x], '=') && ((*envp) == NULL || (*envp)[y] == NULL))
			if (env_add(envp, argv[x]))
				return (1);
		++x;
	}
	return (0);
}
