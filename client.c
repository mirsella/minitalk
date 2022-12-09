#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"


void    sig_handler(int signo, siginfo_t *info, void *context)
{
}

// https://openclassrooms.com/fr/courses/4117396-developpez-en-c-pour-lembarque/4633446-manipulez-les-registres-et-les-masques
int	main(int argc, char **argv)
{
	int		i;
	int		bit;
	int		pid;
	char	c;

	if (argc != 3)
	{
		ft_printf("usage: ./client [pid] [string]\n");
		return (0);
	}

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
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		c = argv[2][i];
		bit = 128;
		// ft_printf("c: %c, decimal: %d\n", c, c);
		while (bit > 0)
		{
			if (c & bit)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			bit >>= 1;
			usleep(100);
		}
		i++;
	}
}
