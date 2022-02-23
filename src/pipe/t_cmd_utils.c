/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:21:50 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/23 02:30:02 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	**init_arr(char ***arr, char *s)
{
	*arr = malloc(sizeof(char *) * 2);
	if (*arr == NULL)
		return (NULL);
	(*arr)[0] = s;
	(*arr)[1] = NULL;
	return (*arr);
}

char	**add_to_arr(char ***arr, char *s)
{
	int		i;
	char	**temp;

	if (*arr == NULL)
		return (init_arr(arr, s));
	i = 0;
	while ((*arr)[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while ((*arr)[i++])
		temp[i - 1] = (*arr)[i - 1];
	temp[i - 1] = s;
	temp[i] = NULL;
	free(*arr);
	*arr = temp;
	return (*arr);
}

t_cmd	*new_t_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->outfile_type = NULL;
	cmd->cmds = NULL;
	cmd->cmdpath = NULL;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->re_in = FALSE;
	cmd->re_out = FALSE;
	cmd->append_out = FALSE;
	cmd->append_in = FALSE;
	cmd->next = NULL;
	return (cmd);
}

void	t_cmd_add_back(t_cmd **head, t_cmd *latest)
{
	t_cmd	*temp;

	temp = *head;
	if (temp == NULL)
		*head = latest;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = latest;
	}
}
