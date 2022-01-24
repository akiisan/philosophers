/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:24 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:35:18 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	ft_take_forks(t_ph *philo)
{
	if (!(philo->index % 2) && philo->index == philo->core->philo_nbr)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(find_fork(philo));
	if (!taking_fork(philo))
		return (0);
	if (!print_fork(philo))
		return (unlock_all(philo, 1));
	if (philo->core->philo_nbr == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	if (!(philo->index % 2) && philo->index == philo->core->philo_nbr)
		pthread_mutex_lock(find_fork(philo));
	else
		pthread_mutex_lock(philo->r_fork);
	if (!print_fork(philo))
		return (unlock_all(philo, 2));
	philo->forks = 1;
	return (1);
}

void	ft_eat(t_ph *philo)
{
	int		nb;
	int		death;

	death = 0;
	nb = philo->index;
	if (philo->index == philo->core->philo_nbr)
		nb = 0;
	if (philo->fork == 0 && philo->core->philo[nb].fork == 0)
		return ;
	philo->meal_num = philo->meal_num + 1;
	death = check_eat(philo);
	if (!print_eating(philo, death))
		return ;
	ft_usleep(philo->etime);
	philo->fork = 0;
	if (philo->index == philo->core->philo_nbr)
		philo->core->philo[0].fork = 0;
	else
		philo->core->philo[philo->index].fork = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(find_fork(philo));
	philo->forks = 0;
}

void	ft_sleep(t_ph *philo)
{
	print_sleeping(philo);
	ft_usleep(philo->stime);
}

void	ft_think(t_ph *philo)
{
	pthread_mutex_lock(philo->m_display);
	if (philo->core->death == 1)
	{
		pthread_mutex_unlock(philo->m_display);
		return ;
	}
	ft_putlnbr(get_time() - philo->core->start);
	ft_putchar(' ');
	ft_putlnbr((unsigned long)philo->index);
	ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(philo->m_display);
}
