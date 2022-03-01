/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:56:01 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/28 21:14:03 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	close_fds(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

int	do_init(t_input *input)
{
	int		i;

	input->here_doc_id = 0;
	input->file_fail = 0;
	input->cmd_chain = NULL;
	input->envp = g_shell_env.envp;
	input->path = NULL;
	i = 0;
	while (g_shell_env.envp[i] && ft_strncmp(g_shell_env.envp[i], "PATH=", 5))
		i++;
	if (g_shell_env.envp[i] == NULL)
		return (0);
	input->path = ft_split(&((g_shell_env.envp)[i][5]), ':');
	if ((input->path) == NULL)
		return (1);
	return (0);
}

static void	do_exec(t_input *input, t_cmd *cmd, int i)
{
	int	j;
	int	k;

	k = i % 2;
	j = !k;
	if ((cmd->infile && cmd->fd[0] < 0) || (cmd->outfile && cmd->fd[1] < 0))
		exit(EXIT_FAILURE);
	if (cmd->infile)
		dup2(cmd->fd[0], STDIN_FILENO);
	else if (i > 0)
		dup2(input->fd[j][0], STDIN_FILENO);
	if (cmd->outfile)
		dup2(cmd->fd[1], STDOUT_FILENO);
	else if (cmd->next)
		dup2(input->fd[k][1], STDOUT_FILENO);
	close_fds(cmd->fd);
	close_fds(input->fd[0]);
	close_fds(input->fd[1]);
	execve(cmd->cmdpath, cmd->cmds, g_shell_env.envp);
	perror(cmd->cmds[0]);
	exit(EXIT_FAILURE);
}

int	exec_cmds(t_input *input, t_cmd *cmds)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (cmds)
	{
		close_fds(input->fd[i % 2]);
		pipe(input->fd[i % 2]);
		open_infile_outfile(cmds);
		if (!check_cmd(input, cmds, i++))
		{
			if (fork() == 0)
				do_exec(input, cmds, i - 1);
		}
		close_fds(cmds->fd);
		cmds = cmds->next;
	}
	close_fds(input->fd[0]);
	close_fds(input->fd[1]);
	while (i--)
		wait(&status);
	return (status);
}
