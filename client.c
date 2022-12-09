/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:41:53 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/09 17:47:54 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"
#include "stdlib.h"

int	g_counter = 0;

void	sig_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		g_counter++;
	}
	else if (signo == SIGUSR2)
	{
		ft_printf("Encountered a error");
		exit(1);
	}
}

void	send_char(char c, int pid)
{
	int		bit;

	// ft_printf("Sending char: %c\n", c);
	bit = 128;
	while (bit > 0)
	{
		if (c & bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		pause();
		bit >>= 1;
	}
}

int	main(int argc, char **argv)
{
	int					i;

	if (argc != 3)
	{
		ft_printf("usage: ./client [pid] [string]\n");
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	i = 0;
	while (argv[2][i])
		send_char(argv[2][i++], ft_atoi(argv[1]));
	send_char(argv[2][i++], ft_atoi(argv[1]));
	if (g_counter == i * 8)
		ft_printf("Message sent\n");
	else
		ft_printf("Message not sent. sent: %d, received %d\n", i, g_counter);
}
