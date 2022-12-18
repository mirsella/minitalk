/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:05:57 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/18 10:30:32 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_CLIENT_H
# define MINITALK_CLIENT_H

#include <signal.h>
#include "libft/libft.h"
#include "unistd.h"
#include "stdlib.h"

typedef struct s_client
{
	int		pid;
	int		i;
	int		bit;
	char	*str;
}	t_client;

#endif
