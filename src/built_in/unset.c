/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:12 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 16:17:12 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

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

static int	env_remove(char ***env, char *var)
{
	size_t	idx;
	char	**new;

	idx = 0;
	while ((*env) && (*env)[idx])
		++idx;
	new = ft_calloc(idx, sizeof(char *));
	if (!new)
		return (1);
	idx = 0;
	while ((*env) && (*env)[idx])
	{
		if ((*env)[idx] != var)
			if (env_add(&new, (*env)[idx]))
				return (1);
		++idx;
	}
	free(*env);
	*env = new;
	return (0);
}

int	unset(char **argv, char ***envp)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (argv && argv[x])
	{
		y = 0;
		while ((*envp) && (*envp)[y])
		{
			if (ft_strncmp(argv[x], (*envp)[y], ft_strchr((*envp)[y], '=') - (*envp)[y]) == 0)
				if (env_remove(envp, (*envp)[y]))
					return (1);
			++y;
		}
		++x;
	}
	return (0);
}
