/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:23:07 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/21 16:27:11 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_server.h"

void	error(int pid)
{
	kill(pid, SIGUSR2);
	exit(1);
}

char	*ft_realloc(char *str, size_t msize, int pid)
{
	char	*new;

	new = ft_calloc(msize, sizeof(char));
	if (!new)
		error(pid);
	if (str)
	{
		ft_strlcpy(new, str, ft_strlen(str) + 1);
		free(str);
		str = NULL;
	}
	return (new);
}
