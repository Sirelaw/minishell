/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:45 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 19:57:54 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
#include <stdlib.h>
#include <termios.h>

void	handle_signals();

#endif
