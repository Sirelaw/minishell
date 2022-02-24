/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:06:27 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/24 16:00:53 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handling.h>

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_shell_env.last_exit_code = 130;
	}
}

static void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		signal(SIGQUIT, SIG_IGN);
		kill(0, SIGQUIT);
		g_shell_env.last_exit_code = 131;
	}
}

void	sig_handle_exec(void)
{
	struct termios	terminal;

	tcgetattr(2, &terminal);
	if (!(terminal.c_lflag & ECHOCTL))
		terminal.c_lflag = terminal.c_lflag ^ ECHOCTL;
	tcsetattr(2, TCSANOW, &terminal);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGSEGV, exit);
}
