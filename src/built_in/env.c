#include <built_in.h>

int	env(char **envp)
{
	size_t	idx;

	idx = 0;
	while (envp[idx])
	{
		printf("%s\n", envp[idx]);
		++idx;
	}
	return (0);
}
