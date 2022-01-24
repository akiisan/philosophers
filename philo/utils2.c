/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:14:49 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:22:15 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

unsigned long	get_time(void)
{
	unsigned long	time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000);
	time += (t.tv_usec / 1000);
	return (time);
}

void	init_philo(t_core *core, t_ph *philo)
{
	int				i;
	unsigned long	time;

	i = 0;
	time = get_time();
	while (i < core->philo_nbr)
	{
		philo[i].core = core;
		philo[i].meal_num = 0;
		philo[i].index = i + 1;
		philo[i].dtime = core->dtime;
		philo[i].sat_eat = core->sat_eat;
		philo[i].etime = core->etime;
		philo[i].stime = core->stime;
		philo[i].last_meal = time;
		if (i > 0)
		{
			philo[i].m_display = philo[i - 1].m_display;
			philo[i].m_core = philo[i - 1].m_core;
			philo[i].m_time = philo[i - 1].m_time;
			philo[i].m_death = philo[i - 1].m_death;
		}
		i++;
	}
}

void	errmalloc(t_ph *philo)
{
	if (philo[0].m_time != NULL)
		free(philo[0].m_display);
	if (philo[0].m_death != NULL)
		free(philo[0].m_display);
	if (philo[0].m_display != NULL)
		free(philo[0].m_display);
	if (philo[0].m_core != NULL)
		free(philo[0].m_display);
	if (philo != NULL)
		free(philo);
	ft_putstr_fd("error malloc failed\n",2);
}

int	give_forks(int ph_nbr, t_ph *philo)
{
	int	i;

	i = 0;
	while (i < ph_nbr)
	{
		philo[i].r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		if (pthread_mutex_init(philo[i].r_fork, NULL) != 0)
		{
			ft_putstr_fd("mutex init failed\n", 2);
			return (0);
		}
		philo[i].fork = 0;
		i++;
	}
	return (1);
}

t_ph	*philo_init(t_core *core, t_ph *philo)
{
	int	error;

	error = 0;
	philo = malloc(sizeof(t_ph) * core->philo_nbr);
	philo[0].m_display = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	philo[0].m_core = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	philo[0].m_time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	philo[0].m_death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (!philo[0].m_display || !philo[0].m_core || !philo[0].m_time
		|| !philo[0].m_death || !philo)
		errmalloc(philo);
	error += pthread_mutex_init(philo[0].m_display, NULL);
	error += pthread_mutex_init(philo[0].m_core, NULL);
	error += pthread_mutex_init(philo[0].m_time, NULL);
	error += pthread_mutex_init(philo[0].m_death, NULL);
	if (error != 0)
	{
		ft_putstr_fd("mutex init failed\n", 1);
		return (NULL);
	}
	init_philo(core, philo);
	if (!give_forks(core->philo_nbr, philo))
		return (NULL);
	return (philo);
}
