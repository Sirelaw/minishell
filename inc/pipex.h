/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:03:23 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/08 18:12:04 by sachmull         ###   ########.fr       */
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
	char			**infile;
	char			**outfile;
	char			**outfile_type;
	char			**cmds;
	char			*cmdpath;
	char			**delimiter;
	int				fd[2];
	int				re_in;
	int				re_out;
	int				append_out;
	int				append_in;
	struct s_cmd	*next;
}t_cmd;


typedef struct s_input
{
	char	**envp;
	char	**path;
	int		fd[2][2];
	t_cmd	*cmd_chain;
}t_input;

int		do_init(char **envp, t_input *input);
int		exec_cmds(t_input *input, t_cmd *cmds);
int		check_cmd(t_input *input, t_cmd *cmd_attr);
t_cmd	*new_t_cmd(void);
void	t_cmd_add_back(t_cmd **head, t_cmd *latest);
void	add_to_array(char ***arr, char *s);
t_cmd	*build_chain(t_lexer *l, t_input *input);

#endif