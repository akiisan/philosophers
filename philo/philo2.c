/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:24 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:34:36 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*start_routine(void *philo)
{
	t_ph	*ph;

	ph = (t_ph *) philo;
	while (1)
	{
		if (!is_one_dead(ph))
		{
			if (!ft_take_forks(ph))
				return (NULL);
		}
		if (ph->core->philo_nbr == 1)
			return (NULL);
		if (!is_one_dead(ph))
			ft_eat(ph);
		if (!is_one_dead(ph))
			ft_sleep(ph);
		if (!is_one_dead(ph))
			ft_think(ph);
		if (!is_dead(ph))
			return (NULL);
	}
	return (NULL);
}

int	monitoring(t_ph *philo)
{
	unsigned long	time;
	static int		philo_number;

	time = get_time();
	pthread_mutex_lock(philo[philo_number].m_time);
	if (time - philo[philo_number].last_meal >= (unsigned long)philo->dtime)
	{
		pthread_mutex_unlock(philo[philo_number].m_time);
		print_death(&philo[philo_number]);
		return (1);
	}
	pthread_mutex_unlock(philo[philo_number].m_time);
	pthread_mutex_lock(philo[philo_number].m_core);
	if (check_satiate(philo, philo_number))
		return (1);
	pthread_mutex_unlock(philo[philo_number].m_core);
	philo_number++;
	if (philo_number >= philo->core->philo_nbr)
		philo_number = 0;
	return (0);
}

void	start_threads(t_core *core)
{
	int		i;

	i = 0;
	core->start = get_time();
	while (i < core->philo_nbr)
	{
		pthread_create(&core->philo[i].thread, NULL, &start_routine,
			(void *)&core->philo[i]);
		usleep(50);
		i = i + 2;
	}
	i = 1;
	while (i < core->philo_nbr)
	{
		pthread_create(&core->philo[i].thread, NULL, &start_routine,
			(void *)&core->philo[i]);
		usleep(50);
		i = i + 2;
	}
	while (!monitoring(core->philo))
		;
}