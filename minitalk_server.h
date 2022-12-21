/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:24:32 by mirsella          #+#    #+#             */
/*   Updated: 2022/12/21 16:27:20 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_SERVER_H
# define MINITALK_SERVER_H

# include "stdlib.h"
# include "unistd.h"
# include "libft/libft.h"
# include <signal.h>
  
char	*ft_realloc(char *str, size_t msize, int pid);
void	error(int pid);

#endif
