/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:41:53 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/21 14:56:22 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"

t_client	g_client;

void	handle_null(void)
{
	if (g_client.received == (ft_strlen(g_client.str) + 1) * 8)
		ft_putstr("message sent successfully");
	else
		ft_putstr("message not sent successfully");
	exit(0);
}

void	kill_wrapper(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		ft_putstr("Error: kill() failed\nprobably wrong PID\n");
		exit(1);
	}
}

void	send_byte(unsigned char c)
{
	if (c & g_client.bit)
		kill_wrapper(g_client.pid, SIGUSR2);
	else
		kill_wrapper(g_client.pid, SIGUSR1);
	g_client.bit >>= 1;
}

void	sig_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		g_client.received++;
		if (g_client.bit == 0)
		{
			if (g_client.str[g_client.i] == 0)
				handle_null();
			else
				g_client.i++;
			g_client.bit = 128;
			send_byte(g_client.str[g_client.i]);
		}
		else
			send_byte(g_client.str[g_client.i]);
	}
	else if (signo == SIGUSR2)
	{
		ft_printf("Server reported an error");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("usage: ./client [pid] [string]\n");
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	g_client.pid = ft_atoi(argv[1]);
	g_client.str = argv[2];
	g_client.received = 0;
	g_client.i = 0;
	g_client.bit = 128;
	send_byte(g_client.str[g_client.i]);
	while (1)
		sleep(1);
}
