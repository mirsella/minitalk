/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:41:50 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/18 10:50:14 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"
#include "stdlib.h"

int		g_oldpid = 0;

char	*ft_realloc(char *str, size_t msize)
{
	char	*new;

	new = ft_calloc(msize, sizeof(char));
	if (str)
	{
		ft_strlcpy(new, str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	return (new);
}

void	handle_char(char c, int pid)
{
	static char		*str = NULL;
	static size_t	msize = 50;

	if (g_oldpid != pid || !str)
	{
		g_oldpid = pid;
		msize = 50;
		str = ft_realloc(NULL, msize);
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
		if (ft_strlen(str) + 1 >= msize)
		{
			msize *= 2;
			str = ft_realloc(str, msize);
		}
		str[ft_strlen(str)] = c;
	}
}

void	sig_handler(int signo, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)context;
	if (g_oldpid != info->si_pid)
	{
		handle_char(0, info->si_pid);
		i = 0;
		c = 0;
	}
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
		// ft_putchar(c);
		i = 0;
		c = 0;
	}
	g_oldpid = info->si_pid;
	kill(info->si_pid, SIGUSR1);
}

int		main(void)
{
	struct sigaction	act;

	ft_printf("pid: %d\n", getpid());
	// sigemptyset(&act.sa_mask);
	// sigaddset(&act.sa_mask, SIGUSR1);
	// sigaddset(&act.sa_mask, SIGUSR2);
	// sigaddset(&act.sa_mask, SIGINT);
	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		sleep(1);
}
