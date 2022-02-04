/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_peek_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:15:04 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 16:15:04 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

char	lex_peek_char(t_lexer *l)
{
	if (l->read_pos > ft_strlen(l->input))
		return (0);
	else
		return (l->input[l->read_pos]);
}
