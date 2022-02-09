/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:11:10 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/09 20:07:18 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i++])
		free(arr[i - 1]);
	if (arr)
		free(arr);
}

void	free_cmd(t_cmd *cmd)
{
	free_arr(cmd->infile);
	free_arr(cmd->outfile);
	free_arr(cmd->outfile_type);
	free_arr(cmd->cmds);
	free(cmd->cmdpath);
	free(cmd);
}

int free_and_exit(int exit_status, t_input *input, int exit_bool)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (!input)
	{
		cmd = input->cmd_chain;
		while (cmd)
		{
			temp = cmd->next;
			free_cmd(cmd);
			cmd = temp;
		}
		free(input);	
	}
	if (exit_bool)
		exit(exit_status);
	return (exit_status);
}

int	pipex(t_lexer *l, t_shell_env *shell_env)
{
	t_input	*input;
	int		i;
	int		exit_code;
    char	**envp;

	exit_code = 0;
	errno = 0;
	i = 0;
	envp = shell_env->envp;
	input = malloc(sizeof(t_input));
	if (!input || do_init(envp, input))
		free_and_exit(EXIT_FAILURE, input, FALSE);
	input->cmd_chain = build_chain(l, input);
	if (input->cmd_chain->cmds)
	{
		pipe(input->fd[0]);
		pipe(input->fd[1]);
		exit_code = exec_cmds(input, input->cmd_chain);
		if (WIFEXITED(exit_code) )
		{
  			shell_env->last_exit_code = WEXITSTATUS(exit_code);
        	printf("exit status was %d\n", shell_env->last_exit_code);
		}
	}
	free_and_exit(EXIT_SUCCESS, input, FALSE);
	return (0);
}
