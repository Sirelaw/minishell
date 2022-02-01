/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:03:23 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/01 10:32:16 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <minishell.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_input
{
	char	*infile;
	char	*outfile;
	char	**cmds;
	char	**envp;
	char	***mcmds;
	char	**path;
	int		cmdcount;
	int		fd[3][2];
	t_list	*mpath;
}t_input;

int		here_doc(int argc, char **argv, char **envp, t_input *input);
int		do_init(int argc, char **argv, char **envp, t_input *input);
int		check_cmds(t_input *input);
int		exec_cmds(t_input *input);
void	ft_free(t_input *input);

#endif