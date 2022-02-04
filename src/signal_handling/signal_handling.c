/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:25 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 19:56:42 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handling.h>
#include <stdlib.h>
#include <termios.h>

static void	handle_signal_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals()
{
	struct termios	terminal;

	tcgetattr(2, &terminal);
	terminal.c_lflag = terminal.c_lflag ^ ECHOCTL;
	tcsetattr(2, TCSANOW, &terminal);
	signal(SIGINT, handle_signal_int);
	signal(SIGQUIT, SIG_IGN);
}
