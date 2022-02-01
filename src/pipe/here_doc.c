/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:41:48 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/01 07:19:54 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*ft_join(char **ret, char c)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*ret)[i])
		i++;
	temp = malloc(i + 2);
	temp[i + 1] = '\0';
	i = 0;
	while ((*ret)[i++])
		temp[i - 1] = (*ret)[i - 1];
	temp[i - 1] = c;
	free(*ret);
	*ret = temp;
	return (0);
}

static void	*get_next_line(char *delimiter, int *fd)
{
	char	*ret;
	char	temp[1];

	*temp = '\0';
	while (1)
	{
		ret = malloc(1);
		ret[0] = '\0';
		while (*temp != '\n')
		{
			if (read(STDIN_FILENO, temp, 1) <= 0)
				return (0);
			if ((*temp == '\n') && (!ft_strcmp(ret, delimiter)))
			{
				free(ret);
				close(fd[1]);
				return (0);
			}	
			ft_join(&ret, *temp);
		}
		write(fd[1], ret, ft_strlen(ret));
		*temp = '\0';
		free(ret);
		ret = NULL;
	}
}

int	here_doc(int argc, char **argv, char **envp, t_input *input)
{
	int		fd[2];

	if (do_init(argc - 1, &(argv[1]), envp, input))
		return (2);
	if (check_cmds(input))
		return (3);
	if (pipe(fd) == -1)
		return (4);
	(input->fd)[0][0] = fd[0];
	get_next_line(argv[2], fd);
	if (exec_cmds(input))
		return (4);
	ft_free(input);
	return (0);
}
