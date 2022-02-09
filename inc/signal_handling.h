/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:45 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/09 15:53:32 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <minishell.h>

void	sig_handle_interactive(void);
void	sig_handle_exec(void);
void	sig_handle_doc(void);

#endif
