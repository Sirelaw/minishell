/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:39:14 by oipadeol          #+#    #+#             */
/*   Updated: 2021/11/16 16:53:00 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_path_cmd(char **path, char *cmd, char *s, t_input *input)
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
			ft_lstadd_back(&(input->mpath), ft_lstnew(s));
			return (0);
		}
		free(s);
	}
	return (-1);
}

static int	malloc_mcmds(t_input *input)
{
	int	count;
	int	i;

	i = 0;
	count = input->cmdcount;
	input->mcmds = ft_calloc(count + 1, sizeof(char **));
	if ((input->mcmds) == NULL)
		return (-1);
	while (i < count)
	{
		(input->mcmds)[i] = ft_split((input->cmds)[i], ' ');
		if ((input->mcmds)[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

int	check_cmds(t_input *input)
{
	int		i;
	int		j;
	int		ret;
	char	*s;

	i = 0;
	j = 0;
	ret = 0;
	s = NULL;
	while (i++ < (input->cmdcount))
	{
		j = check_path_cmd(input->path, (input->cmds)[i - 1], s, input);
		if (j == -1)
			ft_putstr_fd(*((input->cmds) + i - 1), STDOUT_FILENO);
		if (j == -1)
			ft_putstr_fd(": command not found", STDOUT_FILENO);
		if (j == -1)
			ret = 1;
		j = 0;
	}
	if ((!ret) && (malloc_mcmds(input)))
		return (-2);
	return (ret);
}

static void	ft_free_lst(t_list *lst)
{
	t_list	*p;
	t_list	*temp;

	p = lst;
	while (p != NULL)
	{
		free(p->content);
		temp = p;
		p = p->next;
		free(temp);
	}
}

void	ft_free(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((input->mcmds)[i++])
	{
		while ((input->mcmds)[i - 1][j++])
			free((input->mcmds)[i - 1][j - 1]);
		j = 0;
		free((input->mcmds)[i - 1]);
	}
	free(input->mcmds);
	i = 0;
	while ((input->path)[i++])
		free((input->path)[i - 1]);
	free(input->path);
	ft_free_lst(input->mpath);
}
