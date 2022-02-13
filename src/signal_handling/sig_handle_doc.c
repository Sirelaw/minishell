/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:23:31 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/13 18:13:16 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handling.h>

static void	handle_sigint(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		fd = 3;
		while (fd < 2000000)
		{
			close(fd);
			++fd;
		}
		sig_handle_interactive();
		g_shell_env.last_exit_code = 1;
		loop(&g_shell_env);
	}
}

void	sig_handle_doc(void)
{
	struct sigaction	action;

	action.sa_handler = handle_sigint;
	action.sa_flags = action.sa_flags | SA_RESETHAND;
	sigaction(SIGINT, &action, NULL);
	signal(SIGQUIT, SIG_IGN);
}
