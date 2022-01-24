/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:54:41 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 03:19:20 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (!(philo->number % 2) && philo->number == philo->data->philo_nbr)
		pthread_mutex_lock(philo->rfork);
	else
		pthread_mutex_lock(trouver_fork(philo));
	if (!taking_forks(philo))
		return (0);
	if (!display_fork(philo))
		return (ft_unlock(philo, 1));
	if (philo->data->philo_nbr == 1)
	{
		pthread_mutex_unlock(philo->rfork);
		return (0);
	}
	if (!(philo->number % 2) && philo->number == philo->data->philo_nbr)
		pthread_mutex_lock(trouver_fork(philo));
	else
		pthread_mutex_lock(philo->rfork);
	if (!display_fork(philo))
		return (ft_unlock(philo, 2));
	philo->forks = 1;
	return (1);
}

void	ft_eat(t_philo *philo)
{
	int		nb;
	int		death;

	death = 0;
	nb = philo->number;
	if (philo->number == philo->data->philo_nbr)
		nb = 0;
	if (philo->fork == 0 && philo->data->philo[nb].fork == 0)
		return ;
	philo->meals = philo->meals + 1;
	death = ft_check_meals(philo);
	if (!display_eating(philo, death))
		return ;
	ft_usleep(philo->eat_time);
	philo->fork = 0;
	if (philo->number == philo->data->philo_nbr)
		philo->data->philo[0].fork = 0;
	else
		philo->data->philo[philo->number].fork = 0;
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(trouver_fork(philo));
	philo->forks = 0;
}

void	ft_sleep(t_philo *philo)
{
	display_sleeping(philo);
	ft_usleep(philo->sleep_time);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(philo->m_display);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(philo->m_display);
		return ;
	}
	ft_putlongnbr(ft_get_time() - philo->data->start);
	ft_putchar(' ');
	ft_putlongnbr((unsigned long)philo->number);
	ft_putstr(" is thinking\n");
	pthread_mutex_unlock(philo->m_display);
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *) philo;
	while (1)
	{
		if (!is_someone_dead(tmp))
		{
			if (!ft_take_forks(tmp))
				return (NULL);
		}
		if (tmp->data->philo_nbr == 1)
			return (NULL);
		if (!is_someone_dead(tmp))
			ft_eat(tmp);
		if (!is_someone_dead(tmp))
			ft_sleep(tmp);
		if (!is_someone_dead(tmp))
			ft_think(tmp);
		if (!is_dead(tmp))
			return (NULL);
	}
	return (NULL);
}
