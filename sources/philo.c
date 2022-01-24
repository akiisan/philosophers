/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:10:32 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 03:19:17 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	dispatche_forks(int philo_nbr, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo_nbr)
	{
		philo[i].rfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		if (pthread_mutex_init(philo[i].rfork, NULL) != 0)
		{
			printf("mutex init failed\n");
			return (0);
		}
		philo[i].fork = 0;
		i++;
	}
	return (1);
}

t_philo	*set_philo(t_data *data, t_philo *philo)
{
	int	error;

	error = 0;
	philo = malloc(sizeof(t_philo) * data->philo_nbr);
	philo[0].m_display = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	philo[0].m_data = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	philo[0].m_time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	philo[0].m_death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (!philo[0].m_display || !philo[0].m_data || !philo[0].m_time
		|| !philo[0].m_death || !philo)
		ft_error_malloc(philo);
	error += pthread_mutex_init(philo[0].m_display, NULL);
	error += pthread_mutex_init(philo[0].m_data, NULL);
	error += pthread_mutex_init(philo[0].m_time, NULL);
	error += pthread_mutex_init(philo[0].m_death, NULL);
	if (error != 0)
		return (ft_puterror("Error: mutex init failed\n"));
	data_philo(0, data, philo);
	if (!dispatche_forks(data->philo_nbr, philo))
		return (NULL);
	return (philo);
}

int	death_monitoring(t_philo *philo)
{
	unsigned long	time;
	static int		philo_number;

	time = ft_get_time();
	pthread_mutex_lock(philo[philo_number].m_time);
	if (time - philo[philo_number].last_meal >= (unsigned long)philo->die_time)
	{
		pthread_mutex_unlock(philo[philo_number].m_time);
		display_death(&philo[philo_number]);
		return (1);
	}
	pthread_mutex_unlock(philo[philo_number].m_time);
	pthread_mutex_lock(philo[philo_number].m_data);
	if (check_satiate(philo, philo_number))
		return (1);
	pthread_mutex_unlock(philo[philo_number].m_data);
	philo_number++;
	if (philo_number >= philo->data->philo_nbr)
		philo_number = 0;
	return (0);
}

void	launch_threads(t_data *data)
{
	int		i;

	i = 0;
	data->start = ft_get_time();
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine,
			(void *)&data->philo[i]);
		usleep(50);
		i = i + 2;
	}
	i = 1;
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine,
			(void *)&data->philo[i]);
		usleep(50);
		i = i + 2;
	}
	while (!death_monitoring(data->philo))
		;
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philo;

	philo = NULL;
	if (ac != 5 && ac != 6)
	{
		ft_putstr("uncorrect number of arguments\n");
		return (0);
	}
	if (ft_check_argument(ac, av) == -1)
	{
		ft_putstr("unvalid arguments\n");
		return (0);
	}
	init_data(&data);
	if (parse_data(ac, av, &data) < 0)
		return (0);
	data.philo = set_philo(&data, philo);
	if (!data.philo)
		return (0);
	launch_threads(&data);
	ft_clean(&data);
	return (0);
}
