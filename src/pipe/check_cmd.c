/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:23:44 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/05 12:40:30 by oipadeol         ###   ########.fr       */
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

int	check_cmd(t_input *input, t_cmd *cmd_attr)
{
	int		ret;
	char	*s;

	ret = 0;
	s = NULL;
	if (!check_path_cmd(input->path, (cmd_attr->cmds)[0], s, cmd_attr))
		return (0);
	ft_putstr_fd((cmd_attr->cmds)[0], STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	return (1);
}