/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:21:50 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/12 02:01:22 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
