/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:41:53 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/18 10:11:49 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_client.h"

t_client	g_client;

void	send_byte(unsigned char c)
{
	int	i;

	if (c & g_client.bit)
		i = kill(g_client.pid, SIGUSR2);
	else
		i = kill(g_client.pid, SIGUSR1);
	if (i == -1)
		ft_putstr("could not send signal");
	g_client.bit >>= 1;
}

void	sig_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		if (g_client.bit == 0)
		{
			if (g_client.str[g_client.i] == 0)
			{
				ft_printf("Message sent to server");
				exit(0);
			}
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
		ft_printf("Server sent an error");
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
	g_client.i = 0;
	g_client.bit = 128;
	send_byte(g_client.str[g_client.i]);
	while (1)
		sleep(1);
}
