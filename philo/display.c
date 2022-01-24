/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:24 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:35:11 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	print_fork(t_ph *philo)
{
	pthread_mutex_lock(philo->m_display);
	if (philo->core->death == 1)
	{
		pthread_mutex_unlock(philo->m_display);
		return (0);
	}
	ft_putlnbr(get_time() - philo->core->start);
	ft_putchar(' ');
	ft_putlnbr((unsigned long)philo->index);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_unlock(philo->m_display);
	return (1);
}

int	print_eating(t_ph *philo, int death)
{
	pthread_mutex_lock(philo->m_display);
	pthread_mutex_lock(philo->m_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->m_time);
	if (philo->core->death == 1 && death == 0)
	{
		pthread_mutex_unlock(philo->m_display);
		return (0);
	}
	ft_putlnbr(get_time() - philo->core->start);
	ft_putchar(' ');
	ft_putlnbr((unsigned long)philo->index);
	ft_putstr_fd(" is eating\n", 1);
	if (death == 1)
		philo->core->death = 1;
	pthread_mutex_unlock(philo->m_display);
	return (1);
}

void	print_sleeping(t_ph *philo)
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
	ft_putstr_fd(" is sleeping\n", 1);
	pthread_mutex_unlock(philo->m_display);
}

void	print_death(t_ph *philo)
{
	pthread_mutex_lock(philo->m_display);
	pthread_mutex_lock(philo->m_death);
	philo->core->death = 1;
	philo->core->dead = 1;
	pthread_mutex_unlock(philo->m_death);
	ft_putlnbr(get_time() - philo->core->start);
	ft_putchar(' ');
	ft_putlnbr((unsigned long)philo->index);
	ft_putstr_fd(" died\n", 1);
	pthread_mutex_unlock(philo->m_display);
}
