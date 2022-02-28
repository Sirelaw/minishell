/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:44:29 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/28 14:55:20 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	dup_fds(t_input *input, t_cmd *cmd, int i)
{
	int	j;
	int	k;

	k = i % 2;
	j = !k;
	cmd->re_in = dup(STDIN_FILENO);
	cmd->re_out = dup(STDOUT_FILENO);
	if (cmd->infile)
		dup2(cmd->fd[0], STDIN_FILENO);
	else if (i > 0)
		dup2(input->fd[j][0], STDIN_FILENO);
	if (cmd->outfile)
		dup2(cmd->fd[1], STDOUT_FILENO);
	else if (cmd->next)
		dup2(input->fd[k][1], STDOUT_FILENO);
}

static void	restore_fds(t_cmd *cmd)
{
	dup2(cmd->re_in, STDIN_FILENO);
	dup2(cmd->re_out, STDOUT_FILENO);
	close(cmd->re_in);
	close(cmd->re_out);
}

static int	check_built_in(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmds[0], "cd") || !ft_strcmp(cmd->cmds[0], "echo")
		|| !ft_strcmp(cmd->cmds[0], "env") || !ft_strcmp(cmd->cmds[0], "export")
		|| !ft_strcmp(cmd->cmds[0], "pwd")
		|| !ft_strcmp(cmd->cmds[0], "unset")
		|| !ft_strcmp(cmd->cmds[0], "exit"))
		return (1);
	return (0);
}

int	built_in_cmd(t_input *input, t_cmd *cmd, int i)
{
	if (!check_built_in(cmd))
		return (0);
	dup_fds(input, cmd, i);
	if (!ft_strcmp(cmd->cmds[0], "cd"))
		g_shell_env.last_exit_code = cd(cmd->cmds, g_shell_env.envp);
	else if (!ft_strcmp(cmd->cmds[0], "echo"))
		g_shell_env.last_exit_code = echo(cmd->cmds);
	else if (!ft_strcmp(cmd->cmds[0], "env"))
		g_shell_env.last_exit_code = env(g_shell_env.envp);
	else if (!ft_strcmp(cmd->cmds[0], "export"))
		g_shell_env.last_exit_code = export(cmd->cmds, &g_shell_env.envp);
	else if (!ft_strcmp(cmd->cmds[0], "pwd"))
		g_shell_env.last_exit_code = pwd();
	else if (!ft_strcmp(cmd->cmds[0], "unset"))
		g_shell_env.last_exit_code = unset(cmd->cmds, &g_shell_env.envp);
	else if (!ft_strcmp(cmd->cmds[0], "exit"))
		g_shell_env.last_exit_code = built_in_exit(cmd->cmds);
	restore_fds(cmd);
	return (1);
}
