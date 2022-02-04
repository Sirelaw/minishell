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
