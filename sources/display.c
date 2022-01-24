/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:56:57 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 02:59:37 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	display_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->m_display);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(philo->m_display);
		return (0);
	}
	ft_putlongnbr(ft_get_time() - philo->data->start);
	ft_putchar(' ');
	ft_putlongnbr((unsigned long)philo->number);
	ft_putstr(" has taken a fork\n");
	pthread_mutex_unlock(philo->m_display);
	return (1);
}

int	display_eating(t_philo *philo, int death)
{
	pthread_mutex_lock(philo->m_display);
	pthread_mutex_lock(philo->m_time);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->m_time);
	if (philo->data->death == 1 && death == 0)
	{
		pthread_mutex_unlock(philo->m_display);
		return (0);
	}
	ft_putlongnbr(ft_get_time() - philo->data->start);
	ft_putchar(' ');
	ft_putlongnbr((unsigned long)philo->number);
	ft_putstr(" is eating\n");
	if (death == 1)
		philo->data->death = 1;
	pthread_mutex_unlock(philo->m_display);
	return (1);
}

void	display_sleeping(t_philo *philo)
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
	ft_putstr(" is sleeping\n");
	pthread_mutex_unlock(philo->m_display);
}

void	display_death(t_philo *philo)
{
	pthread_mutex_lock(philo->m_display);
	pthread_mutex_lock(philo->m_death);
	philo->data->death = 1;
	philo->data->dead = 1;
	pthread_mutex_unlock(philo->m_death);
	ft_putlongnbr(ft_get_time() - philo->data->start);
	ft_putchar(' ');
	ft_putlongnbr((unsigned long)philo->number);
	ft_putstr(" died\n");
	pthread_mutex_unlock(philo->m_display);
}
