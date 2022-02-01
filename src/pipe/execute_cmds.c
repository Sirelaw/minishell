/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:49:41 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/01 09:48:38 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_all_fds(int fd[3][2])
{
	int	i;

	i = 0;
	while (i++ < 3)
	{
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
}

static void	do_exec(t_input *input, t_list *p, int i)
{
	int	j;
	int	k;

	k = (i % 2) + 1;
	j = 3 - k;
	if (i == 0)
		dup2(input->fd[0][0], STDIN_FILENO);
	else
		dup2(input->fd[j][0], STDIN_FILENO);
	if (i == input->cmdcount - 1)
		dup2(input->fd[0][1], STDOUT_FILENO);
	else
		dup2(input->fd[k][1], STDOUT_FILENO);
	close_all_fds(input->fd);
	execve(p->content, &(((input->mcmds)[i])[0]), input->envp);
	perror(((input->mcmds)[i])[0]);
	exit(EXIT_FAILURE);
}

int	exec_cmds(t_input *input)
{
	int		i;
	pid_t	pid;
	t_list	*p;
	int		k;

	i = 0;
	p = input->mpath;
	while (i < input->cmdcount)
	{
		k = (i % 2) + 1;
		close(input->fd[k][0]);
		close(input->fd[k][1]);
		pipe(input->fd[k]);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			do_exec(input, p, i);
		i++;
		p = p->next;
	}
	close_all_fds(input->fd);
	while (i--)
		wait(NULL);
	return (0);
}
