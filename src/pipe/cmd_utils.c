/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:52:35 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/15 17:57:40 by sachmull         ###   ########.fr       */
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

static void	set_flags(t_cmd *cmd, t_token *tok)
{
	if (tok->type == RE_IN)
		cmd->re_in = TRUE;
	else if (tok->type == RE_OUT)
		cmd->re_out = TRUE;
	else if (tok->type == APPEND_IN)
		cmd->append_in = TRUE;
	else if (tok->type == APPEND_OUT)
		cmd->append_out = TRUE;
}

static void	build_cmd(t_input *ip, t_cmd *cmd, t_token *tok)
{
	set_flags(cmd, tok);
	if ((tok->type == WORD) && (cmd->re_in == TRUE))
	{
		add_to_arr(&cmd->infile, tok->literal);
		cmd->re_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->re_out == TRUE))
	{
		add_to_arr(&cmd->outfile, tok->literal);
		add_to_arr(&cmd->outfile_type, ft_strdup("W"));
		cmd->re_out = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_in == TRUE))
	{
		here_doc(cmd, tok->literal, ip->here_doc_id++);
		cmd->append_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_out == TRUE))
	{
		add_to_arr(&cmd->outfile, tok->literal);
		add_to_arr(&cmd->outfile_type, ft_strdup("A"));
		cmd->append_out = FALSE;
	}
	else if (tok->type == WORD)
		add_to_arr(&cmd->cmds, rm_quotes(expand_str(ip->envp, &tok->literal)));
}

t_cmd	*build_chain(t_lexer *l, t_input *input, t_token tok)
{
	t_cmd	*first_cmd;
	t_cmd	*latest_cmd;
	t_token	peek_tok;

	first_cmd = new_t_cmd();
	if (!first_cmd)
		return (NULL);
	latest_cmd = first_cmd;
	while (tok.type != END && latest_cmd)
	{
		build_cmd(input, latest_cmd, &tok);
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
