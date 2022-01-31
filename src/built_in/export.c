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

int	export(char **argv, char ***envp)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (argv[x])
	{
			y = 0;
			while (ft_strchr(argv[x], '=') && (*envp) && (*envp)[y])
			{
				if (ft_strncmp(argv[x], (*envp)[y], ft_strchr((*envp)[y], '=') \
					- (*envp)[y]) == 0)
				{
					free((*envp)[y]);
					(*envp)[y] = argv[x];
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
