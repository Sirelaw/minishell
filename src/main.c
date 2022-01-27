#include <stdio.h>
#include <minishell.h>

int	loop(t_shell_env *shell_env)
{
	char	*line;

	(void)shell_env;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			;
		if (ft_strlen(line) > 0)
			add_history(line);
		// FOR TESTING ->
		if (lex_valid_syntax(line))
		{
			t_lexer	l = lex_new(line);
			for (t_token t = lex_next_token(&l); t.type != END; t = lex_next_token(&l))
			{
				printf("%s\n", t.literal);
				free(t.literal);
			}
		}
		else
			printf("Invalid syntax\n");
		// <- FOR TESTING
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_env	shell_env;

	shell_env.envp = envp;
	shell_env.last_exit_code = 0;
	handle_signals();
	(void)argc;
	(void)argv;
	loop(&shell_env);
	return (EXIT_SUCCESS);
}
