#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"

// /bin/kill -10 -q 999999 $(getpid a.out)

void    sig_handler(int signo, siginfo_t *info, void *context)
{
	ft_printf("signal %d received with siginfo_t:\n", signo);
	ft_printf("\tsignal number: si_signo=%d\n", info->si_signo);
	ft_printf("\terror number: si_errno=%d\n", info->si_errno);
	ft_printf("\tsignal code: si_code=%d\n", info->si_code);
	ft_printf("\tsignal value union: si_value, sival_int=%d\n", info->si_value.sival_int);
	ft_printf("\tsignal value union: si_value, sival_ptr=%p\n", info->si_value.sival_ptr);
	ft_printf("\tsending process ID: si_pid=%d\n", info->si_pid);
	ft_printf("\tsending process user's ID: si_uid=%d\n", info->si_uid);
	ft_printf("\tfaulting instruction at: si_addr=%p\n", info->si_addr);
	ft_printf("\texit value or signal: si_status=%d\n", info->si_status);
	ft_printf("\tband event for SIGPOLL: si_band=%ld\n", info->si_band);
	ft_printf("\ttimer ID: si_timerid=%d\n", info->si_timerid);
	ft_printf("\toverrun count: si_overrun=%d\n", info->si_overrun);
	ft_printf("\n");
}

int	main(void)
{
	struct sigaction act;

	ft_printf("pid: %d\n", getpid());
	sigemptyset(&act.sa_mask);
	// sigaddset(&act.sa_mask, SIGUSR1);
	// sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (!sleep(1))
		;
}
