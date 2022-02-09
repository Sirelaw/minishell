/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle_interactive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:54:29 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/09 15:17:32 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handling.h>

static void	handle_sigsegv(int sig)
{
	if (sig == SIGSEGV)
	{
		printf("\033[F");
		printf("> exit\n");
		exit(1);
	}
}

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// set $? = 1
	}
}

void	sig_handle_interactive(void)
{
	struct termios	terminal;

	tcgetattr(2, &terminal);
	if (terminal.c_lflag & ECHOCTL)
		terminal.c_lflag = terminal.c_lflag ^ ECHOCTL;
	tcsetattr(2, TCSANOW, &terminal);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, handle_sigsegv);
}
