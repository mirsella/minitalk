/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:39:22 by mirsella          #+#    #+#             */
/*   Updated: 2022/11/23 18:06:45 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static void	count_bytes(int *counter, int byteswrotes)
{
	if (!counter)
		return ;
	if (byteswrotes < 0 || *counter < 0)
		*counter = -1;
	else
		*counter += byteswrotes;
}

int	ft_putstr(char *str)
{
	int	byteswrotes;
	int	i;

	i = 0;
	byteswrotes = 0;
	while (str[i])
	{
		count_bytes(&byteswrotes, ft_putchar(str[i]));
		i++;
	}
	return (byteswrotes);
}
