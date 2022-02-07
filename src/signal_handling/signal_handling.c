/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:25 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/07 14:45:30 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handling.h>

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

void	handle_signals(void)
{
	struct termios	terminal;

	tcgetattr(2, &terminal);
	if (terminal.c_lflag & ECHOCTL)
		terminal.c_lflag = terminal.c_lflag ^ ECHOCTL;
	tcsetattr(2, TCSANOW, &terminal);
	signal(SIGINT, handle_signal_int);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, exit);
}

static void	handle_int_during_exe(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static void	handle_quit_during_exe(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		signal(SIGQUIT, SIG_IGN);
		kill(0, SIGQUIT);
	}
}

void	handle_sig_during_exe(void)
{
	struct termios	terminal;

	tcgetattr(2, &terminal);
	if (!(terminal.c_lflag & ECHOCTL))
		terminal.c_lflag = terminal.c_lflag ^ ECHOCTL;
	tcsetattr(2, TCSANOW, &terminal);
	signal(SIGINT, handle_int_during_exe);
	signal(SIGQUIT, handle_quit_during_exe);
	signal(SIGSEGV, exit);
}
