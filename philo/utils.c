/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:14:49 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:35:33 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long	ft_latoi(const char *str)
{
	long	i;
	long	stock;
	int		neg;

	neg = 1;
	stock = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (neg == -1)
			stock = stock * 10 - (str[i] - 48);
		if (neg == 1)
			stock = stock * 10 + (str[i] - 48);
		i++;
	}
	return (stock);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	get_data(int ac, char **av, t_core *core)
{
	long	tab[5];
	int		n;
	int		i;
	long	num;

	num = 0;
	n = 1;
	while (n < ac)
	{
		tab[num] = ft_latoi(av[n]);
		num++;
		n++;
	}
	core->philo_nbr = tab[0];
	core->dtime = tab[1];
	core->etime = tab[2];
	core->stime = tab[3];
	if (num == 5)
		core->sat_eat = tab[4];
	if (core->philo_nbr < 1 || core->sat_eat == 0)
		return (-1);
	return (0);
}

int	taking_fork(t_ph *philo)
{
	if (!(philo->index % 2) && philo->index == philo->core->philo_nbr)
		philo->fork = 1;
	else if (philo->index == philo->core->philo_nbr)
		philo->core->philo[0].fork = 1;
	else
		philo->core->philo[philo->index].fork = 1;
	if (is_one_dead(philo))
	{
		if (!(philo->index % 2) && philo->index == philo->core->philo_nbr)
			philo->fork = 0;
		else if (philo->index == philo->core->philo_nbr)
			philo->core->philo[0].fork = 0;
		else
			philo->core->philo[philo->index].fork = 0;
		if (!(philo->index % 2) && philo->index == philo->core->philo_nbr)
			pthread_mutex_unlock(philo->r_fork);
		else
			pthread_mutex_unlock(find_fork(philo));
		return (0);
	}
	return (1);
}
