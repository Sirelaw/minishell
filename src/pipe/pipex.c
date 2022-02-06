/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:11:10 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/05 21:39:55 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	do_init(char **envp, t_input *input)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (1);
	input->path = ft_split(&(envp[i][5]), ':');
	if ((input->path) == NULL)
		return (1);
	input->envp = envp;
	input->cmd_chain = NULL;
	return (0);
}

static void	do_exec(t_input *input, t_cmd *cmd, int i)
{
	int	j;
	int	k;

	k = i % 2;
	j = !k;
	if (i > 0)
		dup2(input->fd[j][0], STDIN_FILENO);
	if (cmd->next)
		dup2(input->fd[k][1], STDOUT_FILENO);
	// if ((cmd->fd[0] == -1) && (i > 0))
	// 	dup2(input->fd[j][0], STDIN_FILENO);
	// else if (cmd->fd[0] != -1)
	// 	dup2(cmd->fd[0], STDIN_FILENO);
	// if ((cmd->fd[1] == -1) && cmd->next)
	// 	dup2(input->fd[k][1], STDOUT_FILENO);
	// else if (cmd->fd[1] != -1)
	// 	dup2(cmd->fd[1], STDOUT_FILENO);
	// close_fds(cmd->fd);
	close_fds(input->fd[k]);
	close_fds(input->fd[j]);
	// close_fds(input->fd[1]);
	execve(cmd->cmdpath, cmd->cmds, input->envp);
	perror(cmd->cmds[0]);
	exit(EXIT_FAILURE);
}

int	exec_cmds(t_input *input, t_cmd *cmds)
{
	int		i;
	pid_t	pid;
	int		k;

	i = 0;
	while (cmds)
	{
		check_cmd(input, cmds);
		k = i % 2;
		if (i > 0)
			close_fds(input->fd[k]);
		pipe(input->fd[k]);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			do_exec(input, cmds, i);
		i++;
		cmds = cmds->next;
	}
	close_fds(input->fd[k]);
	while (i--)
		wait(NULL);
	return (0);
}

void	add_to_array(char ***arr, char *s)
{
	int	i;
	char	**temp;

	if (*arr == NULL)
	{
		*arr = malloc(sizeof(char *) * 2);
		(*arr)[0] = s;
		(*arr)[1] = NULL;
		return ;
	}
	i = 0;
	while ((*arr)[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*arr)[i++])
		temp[i - 1] = (*arr)[i - 1];
	temp[i - 1] = s;
	temp[i] = NULL;
	free(*arr);
	*arr = temp;
}

void	build_cmd(t_cmd *cmd, t_token *tok)
{
	if (tok->type == RE_IN)
		cmd->re_in = TRUE;
	else if (tok->type == RE_OUT)
		cmd->re_out = TRUE;
	else if (tok->type == APPEND_IN)
		cmd->append_in = TRUE;
	else if (tok->type == APPEND_OUT)
		cmd->append_out = TRUE;
	if ((tok->type == WORD) && (cmd->re_in == TRUE))
	{
		add_to_array(&cmd->infile, tok->literal);
		cmd->re_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->re_out == TRUE))
	{
		add_to_array(&cmd->outfile, tok->literal);
		cmd->re_out = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_in == TRUE))
	{
		add_to_array(&cmd->delimiter, tok->literal);
		cmd->append_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_out == TRUE))
	{
		add_to_array(&cmd->outfile, tok->literal);
		cmd->append_out = FALSE;
	}
	else if (tok->type == WORD)
		add_to_array(&cmd->cmds, tok->literal);
}

t_cmd	*build_chain(t_lexer *l, t_input *input)
{
	t_cmd	*first_cmd;
	t_cmd	*latest_cmd;
	t_token	tok;
	t_token	peek_tok;

	first_cmd = new_t_cmd();
	latest_cmd = first_cmd;
	tok = lex_next_token(l);
	while (tok.type != END)
	{
		build_cmd(latest_cmd, &tok);
		peek_tok = lex_next_token(l);
		if (peek_tok.type == END || peek_tok.type == PIPE)
		{
			if (peek_tok.type == END)
				return (first_cmd);
			latest_cmd = new_t_cmd();
			t_cmd_add_back(&first_cmd, latest_cmd);
			while (peek_tok.type == PIPE)
				peek_tok = lex_next_token(l);
		}
		tok = peek_tok;
	}
	return (first_cmd);
}

int	pipex(t_lexer *l, char **envp)
{
	t_input	*input;
	int		i;

	errno = 0;
	i = 0;
	input = malloc(sizeof(t_input));
	if (do_init(envp, input))
		exit (EXIT_FAILURE);
	input->cmd_chain = build_chain(l, input);
	if (input->cmd_chain->cmds)
		exec_cmds(input, input->cmd_chain);
	// Testing block
	// if (input->cmd_chain->outfile)
	// 	while (input->cmd_chain->outfile[i])
	// 		printf("%s\n", input->cmd_chain->outfile[i++]);
	//--------------
	// free_all_allocs()
	return (0);
}
