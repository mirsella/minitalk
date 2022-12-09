/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:41:50 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/09 18:03:41 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"
#include "stdlib.h"

char	*g_str = NULL;

char	*store_char(char c, int reset)
{
	static size_t			mallocsize = 25;
	char					*tmp;

	if (reset)
	{
		mallocsize = 25;
		free(g_str);
		g_str = NULL;
	}
	if (!g_str || ft_strlen(g_str) >= mallocsize)
	{
		mallocsize *= 2;
		tmp = g_str;
		g_str = ft_calloc(sizeof(char), mallocsize);
		if (!g_str)
			return (NULL);
		if (tmp)
			ft_strlcpy(g_str, tmp, mallocsize);
		free(tmp);
	}
	g_str[ft_strlen(g_str)] = c;
	return (g_str);
}

void	handle_char(char c, int pid, int reset)
{
	store_char(c, reset);
	if (c == 0)
	{
		if (ft_printf("%s", g_str) == -1)
			kill(pid, SIGUSR2);
		free(g_str);
		g_str = NULL;
	}
	else
	{
		if (!store_char(c, reset))
			kill(pid, SIGUSR2);
	}
}

void	sig_handler(int signo, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;
	static int				pid = 0;

	(void)context;
	if (pid != info->si_pid)
	{
		i = 0;
		c = 0;
		free(g_str);
		g_str = NULL;
	}
	if (signo == SIGUSR2)
	{
		c <<= 1;
		c |= 1;
	}
	else if (signo == SIGUSR1)
	{
		c <<= 1;
	}
	i++;
	if (i == 8)
	{
		handle_char(c, info->si_pid, pid != info->si_pid);
		// ft_putchar(c);
		i = 0;
		c = 0;
	}
	pid = info->si_pid;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

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
		sleep(1);
	}
}
