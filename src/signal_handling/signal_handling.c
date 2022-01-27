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

void	handle_signals()
{
	signal(SIGINT, handle_signal_int);
}
