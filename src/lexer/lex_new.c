/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:15:16 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 16:15:16 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_lexer	lex_new(char *input)
{
	t_lexer	l;

	l.input = input;
	l.pos = 0;
	l.read_pos = 1;
	l.ch = input[0];
	return (l);
}
