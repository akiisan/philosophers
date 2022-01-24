/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:50:04 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:12:22 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	check_numvalue(int ac, char **av)
{
	int		n;
	int		i;

	n = 1;
	while (n < ac)
	{
		i = 0;
		while (av[n][i] != 0)
		{
			while (ft_isdigit(av[n][i]) && av[n][i] != 0)
				i++;
			if ((av[n][i] == '-' || av[n][i] == '+') && i > 0 && av[n][i] != 0)
				return (-1);
			while (av[n][i] == ' ' && av[n][i] != 0)
				i++;
			if ((av[n][i] == '-' || av[n][i] == '+') && av[n][i] != 0)
				i++;
			if (!(ft_isdigit(av[n][i])) && av[n][i] != 0)
				return (-1);
		}
		n++;
	}
	return (1);
}

int	check_intm(int ac, char **av)
{
	int		n;
	int		i;
	long	num;

	n = 1;
	while (n < ac)
	{
		num = ft_latoi(av[n]);
		if (num > 2147483647 || num < -2147483648)
			return (-1);
		n++;
	}
	return (0);
}

int	check_arg(int ac, char **av)
{
	if (check_numvalue(ac, av) == -1 || check_intm(ac, av) == -1)
		return (-1);
}

int	check_eat(t_ph *philo)
{
	int		death;

	death = 0;
	if (philo->meal_num == philo->sat_eat)
	{
		pthread_mutex_lock(philo->m_core);
		philo->core->satiate_nbr = philo->core->satiate_nbr + 1;
		if (philo->core->satiate_nbr == philo->core->philo_nbr)
			death = 1;
		pthread_mutex_unlock(philo->m_core);
	}
	return (death);
}

int	check_satiate(t_ph *philo, int philo_number)
{
	if (philo->core->satiate_nbr == philo->core->philo_nbr)
	{
		pthread_mutex_lock(philo->m_display);
		philo->core->death = 1;
		philo[philo_number].core->satiate = 1;
		pthread_mutex_unlock(philo->m_display);
		pthread_mutex_unlock(philo[philo_number].m_core);
		return (1);
	}
	return (0);
}
