/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:38:30 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 02:49:23 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data)
{
	data->die_time = 0;
	data->eat_nbr = -1;
	data->eat_time = 0;
	data->philo_nbr = 0;
	data->sleep_time = 0;
	data->dead = 0;
	data->satiate_nbr = 0;
	data->satiate = 0;
	data->philo = NULL;
	data->death = 0;
}

void	init_philo(t_philo *philo)
{
	philo->die_time = 0;
	philo->eat_nbr = -1;
	philo->eat_time = 0;
	philo->time_eat = 0;
	philo->rfork = NULL;
	philo->m_display = NULL;
	philo->m_data = NULL;
	philo->m_time = NULL;
	philo->m_death = NULL;
	philo->sleep_time = 0;
	philo->thread = 0;
	philo->meals = 0;
	philo->forks = 0;
}

pthread_mutex_t	*trouver_fork(t_philo *philo)
{
	pthread_mutex_t	*rendu;
	int				nb;
	int				philo_number;

	nb = philo->number;
	philo_number = philo->data->philo_nbr;
	if (nb == philo_number)
		rendu = philo->data->philo[0].rfork;
	else
		rendu = philo->data->philo[nb].rfork;
	return (rendu);
}

int	is_dead(t_philo *philo)
{
	if (is_someone_dead(philo) == 1)
	{
		if (philo->forks == 1)
			unlock_forks(philo);
		return (0);
	}
	return (1);
}

int	check_satiate(t_philo *philo, int philo_number)
{
	if (philo->data->satiate_nbr == philo->data->philo_nbr)
	{
		pthread_mutex_lock(philo->m_display);
		philo->data->death = 1;
		philo[philo_number].data->satiate = 1;
		pthread_mutex_unlock(philo->m_display);
		pthread_mutex_unlock(philo[philo_number].m_data);
		return (1);
	}
	return (0);
}
