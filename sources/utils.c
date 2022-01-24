/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:02:42 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 01:11:36 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putlongnbr(unsigned long nb)
{
	if (nb > 9)
	{
		ft_putlongnbr(nb / 10);
		ft_putlongnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
}

unsigned long	ft_get_time(void)
{
	unsigned long	time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000);
	time += (t.tv_usec / 1000);
	return (time);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	starttime;

	starttime = ft_get_time();
	while (starttime + time > ft_get_time())
		usleep(500);
	return ;
}
