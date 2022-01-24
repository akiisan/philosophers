/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 02:46:09 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 02:34:16 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_clean(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		(void)pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(data->philo[i].rfork);
		free(data->philo[i].rfork);
		i++;
	}
	pthread_mutex_destroy(data->philo[0].m_display);
	pthread_mutex_destroy(data->philo[0].m_time);
	pthread_mutex_destroy(data->philo[0].m_data);
	pthread_mutex_destroy(data->philo[0].m_death);
	free(data->philo[0].m_display);
	free(data->philo[0].m_time);
	free(data->philo[0].m_data);
	free(data->philo[0].m_death);
	free(data->philo);
}

void	*ft_puterror(char *str)
{
	ft_putstr(str);
	return (NULL);
}

void	*ft_error_malloc(t_philo *philo)
{
	if (philo[0].m_display != NULL)
		free(philo[0].m_display);
	if (philo[0].m_data != NULL)
		free(philo[0].m_display);
	if (philo[0].m_time != NULL)
		free(philo[0].m_display);
	if (philo[0].m_death != NULL)
		free(philo[0].m_display);
	if (philo != NULL)
		free(philo);
	return (ft_puterror("Error: allocation issue\n"));
}

int	ft_unlock(t_philo *philo, int i)
{
	if (i == 1)
	{
		if (!(philo->number % 2))
			pthread_mutex_unlock(philo->rfork);
		else
			pthread_mutex_unlock(trouver_fork(philo));
		return (0);
	}
	if (i == 2)
	{
		if (!(philo->number % 2))
			pthread_mutex_unlock(philo->rfork);
		else
			pthread_mutex_unlock(trouver_fork(philo));
		if (!(philo->number % 2))
			pthread_mutex_unlock(trouver_fork(philo));
		else
			pthread_mutex_unlock(philo->rfork);
		return (0);
	}
	return (0);
}

int	ft_check_meals(t_philo *philo)
{
	int		death;

	death = 0;
	if (philo->meals == philo->eat_nbr)
	{
		pthread_mutex_lock(philo->m_data);
		philo->data->satiate_nbr = philo->data->satiate_nbr + 1;
		if (philo->data->satiate_nbr == philo->data->philo_nbr)
			death = 1;
		pthread_mutex_unlock(philo->m_data);
	}
	return (death);
}
