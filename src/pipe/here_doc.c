/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:41:48 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/09 19:52:41 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	read_to_fd(int fd, char *delimiter)
{
	char	*temp;

	sig_handle_doc();
	temp = readline("--> ");
	while (temp && ft_strcmp(temp, delimiter))
	{
		temp = expand_str(shell_env.envp, &temp);
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(temp);
		temp = readline("--> ");
	}
	free(temp);
	sig_handle_exec();
}

int	here_doc(t_cmd *cmd, char *delimiter, int here_doc_id)
{
	int 	fd;
	char	*s;
	char	*temp;

	temp = ft_itoa(here_doc_id);
	s =  ft_strjoin("./src/here_docs/", temp);
	free(temp);
	unlink(s);
	fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		perror("Could not open heredoc");
		return(1);
	}
	read_to_fd(fd, delimiter);
	add_to_array(&cmd->infile, s);
	return (0);
}
