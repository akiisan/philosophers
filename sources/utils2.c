/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 03:28:11 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 01:55:01 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	ft_longatoi(const char *str)
{
	long long	i;
	int			neg;
	long long	stock;

	i = 0;
	neg = 1;
	stock = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (neg == -1)
			stock = (stock * 10) - (str[i] - 48);
		else
			stock = (stock * 10) + (str[i] - 48);
		i++;
	}
	return (stock);
}

void	data_philo(int i, t_data *data, t_philo *philo)
{
	unsigned long	time;

	time = ft_get_time();
	while (i < data->philo_nbr)
	{
		philo[i].data = data;
		philo[i].meals = 0;
		philo[i].number = i + 1;
		philo[i].die_time = data->die_time;
		philo[i].eat_nbr = data->eat_nbr;
		philo[i].eat_time = data->eat_time;
		philo[i].sleep_time = data->sleep_time;
		philo[i].last_meal = time;
		if (i > 0)
		{
			philo[i].m_display = philo[i - 1].m_display;
			philo[i].m_data = philo[i - 1].m_data;
			philo[i].m_time = philo[i - 1].m_time;
			philo[i].m_death = philo[i - 1].m_death;
		}
		i++;
	}
}

int	is_someone_dead(t_philo *philo)
{
	int		dead;
	int		satiate;

	dead = 0;
	satiate = 0;
	pthread_mutex_lock(philo->m_death);
	pthread_mutex_lock(philo->m_data);
	dead = philo->data->dead;
	satiate = philo->data->satiate;
	pthread_mutex_unlock(philo->m_death);
	pthread_mutex_unlock(philo->m_data);
	return (dead || satiate);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(trouver_fork(philo));
}

int	taking_forks(t_philo *philo)
{
	if (!(philo->number % 2) && philo->number == philo->data->philo_nbr)
		philo->fork = 1;
	else if (philo->number == philo->data->philo_nbr)
		philo->data->philo[0].fork = 1;
	else
		philo->data->philo[philo->number].fork = 1;
	if (is_someone_dead(philo))
	{
		if (!(philo->number % 2) && philo->number == philo->data->philo_nbr)
			philo->fork = 0;
		else if (philo->number == philo->data->philo_nbr)
			philo->data->philo[0].fork = 0;
		else
			philo->data->philo[philo->number].fork = 0;
		if (!(philo->number % 2) && philo->number == philo->data->philo_nbr)
			pthread_mutex_unlock(philo->rfork);
		else
			pthread_mutex_unlock(trouver_fork(philo));
		return (0);
	}
	return (1);
}
