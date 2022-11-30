/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:57:21 by mirsella          #+#    #+#             */
/*   Updated: 2022/11/23 15:58:48 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_llmax(long long a, long long b)
{
	if (a > b)
		return (a);
	return (b);
}

unsigned long long	ft_ullmax(unsigned long long a, unsigned long long b)
{
	if (a > b)
		return (a);
	return (b);
}

long long	ft_llmin(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
