/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:56:01 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/12 02:00:32 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	do_init(t_input *input)
{
	int		i;
	char	**envp;

	envp = shell_env.envp;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (1);
	input->path = ft_split(&(envp[i][5]), ':');
	if ((input->path) == NULL)
		return (1);
	input->here_doc_id = 0;
	input->envp = envp;
	input->cmd_chain = NULL;
	return (0);
}

int	open_infile_outfile(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->infile && cmd->infile[i++])
	{
		cmd->fd[0] = open(cmd->infile[i - 1], O_RDONLY);
		if (cmd->fd[0] < 0)
			perror(cmd->infile[i - 1]);
		if (cmd->fd[0] < 0)
			return (1);
	}
	i = 0;
	while (cmd->outfile && cmd->outfile[i++])
	{
		if (*(cmd->outfile_type[i - 1]) == 'A')
			cmd->fd[1] = open(cmd->outfile[i - 1], O_WRONLY
					| O_CREAT | O_APPEND, 0666);
		else
			cmd->fd[1] = open(cmd->outfile[i - 1], O_WRONLY
					| O_CREAT | O_TRUNC, 0666);
		if (cmd->fd[1] < 0)
			perror(cmd->outfile[i - 1]);
		if (cmd->fd[1] < 0)
			return (1);
	}
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
	execve(cmd->cmdpath, cmd->cmds, input->envp);
	perror(cmd->cmds[0]);
	exit(EXIT_FAILURE);
}

int	exec_cmds(t_input *input, t_cmd *cmds)
{
	int		i;
	pid_t	pid;
	int		k;
	int		status;

	i = 0;
	status = 0;
	while (cmds)
	{
		k = i % 2;
		close_fds(input->fd[k]);
		pipe(input->fd[k]);
		open_infile_outfile(cmds);
		if (check_cmd(input, cmds, i++))
		{
			close_fds(cmds->fd);
			cmds = cmds->next;
			continue ;
		}
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			do_exec(input, cmds, i - 1);
		close_fds(cmds->fd);
		cmds = cmds->next;
	}
	close_fds(input->fd[0]);
	close_fds(input->fd[1]);
	while (i--)
		wait(&status);
	return (status);
}
