/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:50:04 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:35:41 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	is_dead(t_ph *philo)
{
	if (is_one_dead(philo) == 1)
	{
		if (philo->forks == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(find_fork(philo));
		}
		return (0);
	}
	return (1);
}

int	is_one_dead(t_ph *philo)
{
	int		dead;
	int		satiate;

	dead = 0;
	satiate = 0;
	pthread_mutex_lock(philo->m_death);
	pthread_mutex_lock(philo->m_core);
	dead = philo->core->dead;
	satiate = philo->core->satiate;
	pthread_mutex_unlock(philo->m_death);
	pthread_mutex_unlock(philo->m_core);
	return (dead || satiate);
}

void	clean_philo(t_core *core)
{
	int		i;

	i = 0;
	while (i < core->philo_nbr)
	{
		(void)pthread_join(core->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < core->philo_nbr)
	{
		pthread_mutex_destroy(core->philo[i].r_fork);
		free(core->philo[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(core->philo[0].m_display);
	pthread_mutex_destroy(core->philo[0].m_time);
	pthread_mutex_destroy(core->philo[0].m_core);
	pthread_mutex_destroy(core->philo[0].m_death);
	free(core->philo[0].m_display);
	free(core->philo[0].m_time);
	free(core->philo[0].m_core);
	free(core->philo[0].m_death);
	free(core->philo);
}

int	core_init(int ac, char **av, t_core *core)
{
	core->sat_eat = -1;
	core->dead = 0;
	core->satiate = 0;
	core->satiate_nbr = 0;
	core->start = 0;
	core->death = 0;
	core->philo = NULL;
	if (get_data(ac, av, core) == -1)
		return (-1);
	return (0);
}
