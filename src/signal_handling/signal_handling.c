/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:25 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 19:24:01 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal_handling.h>
#include <stdlib.h>

static void	handle_signal_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\033[K");
		printf("> ");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals()
{
	signal(SIGINT, handle_signal_int);
	signal(SIGQUIT, SIG_IGN);
}
