#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"

// https://openclassrooms.com/fr/courses/4117396-developpez-en-c-pour-lembarque/4633446-manipulez-les-registres-et-les-masques
void    sig_handler(int signo, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;
	(void)context;

	if (signo == SIGUSR2)
	{
		// ft_printf("received SIGUSR2: 1\n");
		c <<= 1;
		c |= 1;
	}
	else if (signo == SIGUSR1)
	{
		// ft_printf("received SIGUSR1: 0\n");
		c <<= 1;
	}
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
