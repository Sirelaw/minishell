/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:52:35 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/08 18:40:07 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

static void	build_cmd(t_input *input, t_cmd *cmd, t_token *tok)
{
	set_flags(cmd, tok);
	if ((tok->type == WORD) && (cmd->re_in == TRUE))
	{
		add_to_array(&cmd->infile, tok->literal);
		cmd->re_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->re_out == TRUE))
	{
		add_to_array(&cmd->outfile, tok->literal);
		add_to_array(&cmd->outfile_type, ft_strdup("W"));
		cmd->re_out = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_in == TRUE))
	{
		here_doc(cmd, tok->literal, input->here_doc_id++);
		cmd->append_in = FALSE;
	}
	else if ((tok->type == WORD) && (cmd->append_out == TRUE))
	{
		add_to_array(&cmd->outfile, tok->literal);
		add_to_array(&cmd->outfile_type, ft_strdup("A"));
		cmd->append_out = FALSE;
	}
	else if (tok->type == WORD)
		add_to_array(&cmd->cmds, expand_str(input->envp, &tok->literal));
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
