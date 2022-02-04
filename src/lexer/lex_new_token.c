/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:15:45 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 16:15:45 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_token	lex_new_token(t_type type, char *literal)
{
	t_token	tok;

	tok.type = type;
	tok.literal = literal;
	return (tok);
}
