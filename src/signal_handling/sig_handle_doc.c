/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:23:31 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/10 17:51:03 by sachmull         ###   ########.fr       */
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
		//rl_redisplay();
		// close all fds
		sig_handle_interactive();
		loop(&shell_env);
		// $? = 1
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
