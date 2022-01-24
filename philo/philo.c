/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:24 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:34:24 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	main(int ac, char **av)
{
	t_core	core;
	t_ph	*philo;

	philo = NULL;
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("error number of arguments\n", 2);
		return (0);
	}
	if (check_arg(ac, av) == -1)
	{
		ft_putstr_fd("error wrong arguments\n", 2);
		return (0);
	}
	if (core_init(ac, av, &core) == -1)
	{
		ft_putstr_fd("error\n", 2);
		return (0);
	}
	philo = philo_init(&core, philo);
	if (philo == NULL)
		return (0);
	core.philo = philo;
	start_threads(&core);
	clean_philo(&core);
	return (0);
}