/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:41:50 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/21 16:27:40 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_server.h"

int		g_oldpid = 0;

void	handle_char(char c, int pid)
{
	static char		*str = NULL;
	static size_t	msize = 50;

	if (g_oldpid != pid || !str)
	{
		g_oldpid = pid;
		msize = 50;
		str = ft_realloc(NULL, msize, pid);
	}
	if (c == 0)
	{
		ft_putstr(str);
		msize = 50;
		free(str);
		str = NULL;
	}
	else
	{
		if (ft_strlen(str) + 1 == msize)
		{
			msize *= 2;
			str = ft_realloc(str, msize, pid);
		}
		str[ft_strlen(str)] = c;
	}
}

void	handle_new_pid(int *i, unsigned char *c, int pid)
{
	if (pid != g_oldpid)
	{
		*i = 0;
		*c = 0;
		handle_char(0, pid);
	}
}

void	sig_handler(int signo, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)context;
	handle_new_pid(&i, &c, info->si_pid);
	if (signo == SIGUSR2)
	{
		c <<= 1;
		c |= 1;
	}
	else if (signo == SIGUSR1)
		c <<= 1;
	i++;
	if (i == 8)
	{
		handle_char(c, info->si_pid);
		i = 0;
		c = 0;
	}
	g_oldpid = info->si_pid;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("pid: %d\n", getpid());
	act.sa_sigaction = sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		sleep(1);
}
