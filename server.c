#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"

void    sig_handler(int signo, siginfo_t *info, void *context)
{

}

int	main(void)
{
	struct sigaction act;

	ft_printf("pid: %d\n", getpid());
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
}
