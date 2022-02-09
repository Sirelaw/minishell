/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:23:44 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/09 15:20:12 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void dup_fds(t_input *input, t_cmd *cmd, int i)
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

void	restore_fds(t_input *input, t_cmd *cmd)
{
	dup2(cmd->re_in, STDIN_FILENO);
	dup2(cmd->re_out, STDOUT_FILENO);
}

int	built_in_cmd(t_input *input, t_cmd *cmd, int i)
{
	if (!(!ft_strcmp(cmd->cmds[0], "cd") || !ft_strcmp(cmd->cmds[0], "echo")
		|| !ft_strcmp(cmd->cmds[0], "env") || !ft_strcmp(cmd->cmds[0], "export")
		|| !ft_strcmp(cmd->cmds[0], "pwd") || !ft_strcmp(cmd->cmds[0], "unset")))
		return (0);
	dup_fds(input, cmd, i);
	if (!ft_strcmp(cmd->cmds[0], "cd"))
		cd(cmd->cmds, input->envp);
	else if (!ft_strcmp(cmd->cmds[0], "echo"))
		echo(cmd->cmds);
	else if (!ft_strcmp(cmd->cmds[0], "env"))
		env(input->envp);
	else if (!ft_strcmp(cmd->cmds[0], "export"))
		export(cmd->cmds, &input->envp);
	else if (!ft_strcmp(cmd->cmds[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->cmds[0], "unset"))
		unset(cmd->cmds, &input->envp);
	restore_fds(input, cmd);
	return (1);
}

static int	check_path_cmd(char **path, char *cmd, char *s, t_cmd *cmd_attr)
{
	int	i;
	int	k;
	int	l;

	i = 0;
	while (path[i++])
	{
		s = ft_calloc(ft_strlen(path[i - 1]) + ft_strlen(cmd) + 2, 1);
		if (s == NULL)
			return (2);
		k = 0;
		l = 0;
		while (path[i - 1][l++])
			s[l - 1] = path[i - 1][l - 1];
		s[l - 1] = '/';
		while ((cmd[k++]) && (cmd[k - 1] != ' '))
			s[l++] = cmd[k - 1];
		if (!(access(s, X_OK)))
		{
			cmd_attr->cmdpath = s;
			return (0);
		}
		free(s);
	}
	return (1);
}

int	check_cmd(t_input *input, t_cmd *cmd_attr, int i)
{
	int		ret;
	char	*s;

	ret = 0;
	s = NULL;
	if (built_in_cmd(input, cmd_attr, i))
		return (1);
	if (ft_strnstr((cmd_attr->cmds)[0], "/", ft_strlen((cmd_attr->cmds)[0])))
	{
		if (!(access((cmd_attr->cmds)[0], X_OK)))
		{
			cmd_attr->cmdpath = ft_strdup((cmd_attr->cmds)[0]);
			return (0);
		}
	}
	else if (!check_path_cmd(input->path, (cmd_attr->cmds)[0], s, cmd_attr))
			return (0);
	ft_putstr_fd((cmd_attr->cmds)[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (1);
}