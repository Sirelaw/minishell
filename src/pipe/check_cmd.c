/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:23:44 by oipadeol          #+#    #+#             */
/*   Updated: 2022/03/01 19:02:05 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

int	check_cmd(t_input *input, t_cmd *cmd, int i)
{
	char	*s;

	s = NULL;
	if ((cmd->infile && cmd->fd[0] < 0) || (cmd->outfile && cmd->fd[1] < 0))
		g_shell_env.last_exit_code = 1;
	if ((cmd->infile && cmd->fd[0] < 0) || (cmd->outfile && cmd->fd[1] < 0))
		return (1);
	if (built_in_cmd(input, cmd, i))
		return (1);
	g_shell_env.last_exit_code = 0;
	if (ft_strnstr((cmd->cmds)[0], "/", ft_strlen((cmd->cmds)[0]))
		|| !(input->path))
	{
		if (!(access((cmd->cmds)[0], X_OK)))
		{
			cmd->cmdpath = ft_strdup((cmd->cmds)[0]);
			return (0);
		}
	}
	else if (!check_path_cmd(input->path, (cmd->cmds)[0], s, cmd))
		return (0);
	ft_putstr_fd((cmd->cmds)[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_shell_env.last_exit_code = 127;
	return (1);
}
