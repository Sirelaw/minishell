/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:03:23 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/04 17:11:40 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <minishell.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef enum e_bool {	FALSE,
						TRUE} t_bool;

typedef struct s_cmd
{
	char	**infile;
	char	**outfile;
	char	*cmd;
	char	**mcmds;
	char	*cmdpath;
	char	**delimiter;
	int		re_in;
	int		re_out;
	int		append_out;
	int		append_in;
	void	*next;
}t_cmd;


typedef struct s_input
{
	char	**envp;
	char	**path;
	int		fd[2][2];
	t_cmd	*cmd_attr;
}t_input;

// int		here_doc(int argc, char **argv, char **envp, t_input *input);
// int		do_init(char **cmd_chain, char **envp, t_input *input);
// int		check_cmds(t_input *input);
// int		exec_cmds(t_input *input);
// void	ft_free(t_input *input);

#endif