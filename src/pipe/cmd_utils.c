/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:52:35 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/28 15:34:45 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	if ((tok->type == RE_IN) || (tok->type == RE_OUT)
		|| (tok->type == APPEND_IN) || (tok->type == APPEND_OUT))
		free(tok->literal);
}

static void	build_cmd(t_input *ip, t_cmd *cmd, t_token *tok)
{
	set_flags(cmd, tok);
	if ((tok->type == WORD) && (cmd->re_in == TRUE))
	{
		add_in_to_arr(&cmd->infile, rm_quotes(tok->literal));
		cmd->re_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->re_out == TRUE))
	{
		add_out_to_arr(&cmd->outfile, rm_quotes(tok->literal), 'W');
		add_to_arr(&cmd->outfile_type, ft_strdup("W"));
		cmd->re_out = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_in == TRUE))
	{
		here_doc(cmd, rm_quotes(tok->literal), ip->here_doc_id++);
		cmd->append_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_out == TRUE))
	{
		add_out_to_arr(&cmd->outfile, rm_quotes(tok->literal), 'A');
		add_to_arr(&cmd->outfile_type, ft_strdup("A"));
		cmd->append_out = FALSE;
	}
	else if (tok->type == WORD)
		add_to_arr(&cmd->cmds, rm_quotes(expand_str(ip->envp, &tok->literal)));
}

static void	builder(t_lexer *l, t_input *input, t_cmd **first_cmd)
{
	t_cmd	*latest_cmd;
	t_token	tok;
	t_token	peek_tok;

	tok = lex_next_token(l);
	latest_cmd = *first_cmd;
	while (tok.type != END && latest_cmd)
	{
		build_cmd(input, latest_cmd, &tok);
		peek_tok = lex_next_token(l);
		if (peek_tok.type == END || peek_tok.type == PIPE)
		{
			if (peek_tok.type == END)
				return (free(peek_tok.literal));
			latest_cmd = new_t_cmd();
			t_cmd_add_back(first_cmd, latest_cmd);
			if (peek_tok.type == PIPE)
				free(peek_tok.literal);
			if (peek_tok.type == PIPE)
				peek_tok = lex_next_token(l);
		}
		tok = peek_tok;
	}
	return (free(tok.literal));
}

t_cmd	*build_chain(t_lexer *l, t_input *input)
{
	t_cmd	*first_cmd;

	first_cmd = new_t_cmd();
	if (!first_cmd)
		return (NULL);
	builder(l, input, &first_cmd);
	return (first_cmd);
}
