/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:03:23 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/28 18:01:19 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <minishell.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/wait.h>
# include <errno.h>

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef struct s_cmd
{
	char			**infile;
	char			**outfile;
	char			**outfile_type;
	char			**cmds;
	char			*cmdpath;
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
	int		here_doc_id;
	int		file_fail;
	int		fd[2][2];
	t_cmd	*cmd_chain;
}t_input;

int		do_init(t_input *input);
int		exec_cmds(t_input *input, t_cmd *cmds);
int		built_in_cmd(t_input *input, t_cmd *cmd, int i);
int		open_infile_outfile(t_cmd *cmd);
int		check_cmd(t_input *input, t_cmd *cmd_attr, int i);
t_cmd	*new_t_cmd(void);
void	t_cmd_add_back(t_cmd **head, t_cmd *latest);
char	**add_to_arr(char ***arr, char *s);
void	add_in_to_arr(char ***arr, char *infile, t_input *input);
void	add_out_to_arr(char ***arr, char *outfile, char mode, t_input *input);
int		here_doc(t_cmd *cmd, char *delimiter, int here_doc_id);
void	free_arr(char **arr);
void	free_all(t_input *input);
t_cmd	*build_chain(t_lexer *l, t_input *input);
void	close_fds(int fd[2]);

#endif