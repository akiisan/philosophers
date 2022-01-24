/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:14:49 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:20:33 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putlnbr(unsigned long nb)
{
	if (nb > 9)
	{
		ft_putlnbr(nb / 10);
		ft_putlnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while (start + time > get_time())
		usleep(500);
	return ;
}

pthread_mutex_t	*find_fork(t_ph *philo)
{
	pthread_mutex_t	*fork;
	int				n;
	int				philo_number;

	n = philo->index;
	philo_number = philo->core->philo_nbr;
	if (n == philo_number)
		fork = philo->core->philo[0].r_fork;
	else
		fork = philo->core->philo[n].r_fork;
	return (fork);
}

int	unlock_all(t_ph *philo, int i)
{
	if (i == 1)
	{
		if (!(philo->index % 2))
			pthread_mutex_unlock(philo->r_fork);
		else
			pthread_mutex_unlock(find_fork(philo));
		return (0);
	}
	if (i == 2)
	{
		if (!(philo->index % 2))
			pthread_mutex_unlock(philo->r_fork);
		else
			pthread_mutex_unlock(find_fork(philo));
		if (!(philo->index % 2))
			pthread_mutex_unlock(find_fork(philo));
		else
			pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	return (0);
}