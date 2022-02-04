/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_read_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:15:00 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 16:15:00 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	lex_read_char(t_lexer *l)
{
	if (l->read_pos > ft_strlen(l->input))
		l->ch = 0;
	else
		l->ch = l->input[l->read_pos];
	l->pos = l->read_pos;
	++l->read_pos;
}
