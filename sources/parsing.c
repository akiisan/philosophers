/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:24:32 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/28 01:19:10 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isnum(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}

void	ft_read_argument(int ac, char **av, long long *tab)
{
	int		arg;
	int		i;
	int		tabincr;

	arg = 1;
	tabincr = 0;
	while (arg < ac)
	{
		i = 0;
		while (av[arg][i] != 0)
		{
			while ((av[arg][i] == ' ' || av[arg][i] == '-') && av[arg][i] != 0)
				i++;
			if (ft_isnum(av[arg][i]))
			{
				tab[tabincr] = ft_longatoi(av[arg] + i);
				if (av[arg][i - 1] == '-')
					tab[tabincr] = tab[tabincr] * -1;
				tabincr++;
			}
			while (ft_isnum(av[arg][i]) && av[arg][i] != 0)
				i++;
		}
		arg++;
	}
}

int	ft_check_argument(int ac, char **av)
{
	int		arg;
	int		i;
	int		argnum;

	arg = 1;
	argnum = 0;
	while (arg < ac)
	{
		i = 0;
		while (av[arg][i] != 0)
		{
			if (ft_isnum(av[arg][i]))
				argnum++;
			while (ft_isnum(av[arg][i]) && av[arg][i] != 0)
				i++;
			while (av[arg][i] == ' ' && av[arg][i] != 0)
				i++;
			if (av[arg][i] == '-' && av[arg][i] != 0)
				i++;
			if (!(ft_isnum(av[arg][i])) && av[arg][i] != 0)
				return (-1);
		}
		arg++;
	}
	return (argnum);
}

int	ft_checkvalues(int ac, long long *tab)
{
	int		i;

	i = 0;
	while (i < ac - 1)
	{
		if (tab[i] > 2147483647 || tab[i] < -2147483647 - 1)
			return (0);
		i++;
	}
	return (1);
}

int	parse_data(int ac, char **av, t_data *data)
{
	long long	*tab;

	tab = malloc(sizeof(long long) * 5);
	if (!tab)
		return (-1);
	tab[4] = -1;
	ft_read_argument(ac, av, tab);
	if (!ft_checkvalues(ac, tab))
	{
		ft_putstr("no int value\n");
		free(tab);
		return (-1);
	}
	data->philo_nbr = tab[0];
	data->die_time = tab[1];
	data->eat_time = tab[2];
	data->sleep_time = tab[3];
	if (tab[4] != -1)
		data->eat_nbr = tab[4];
	free(tab);
	if (data->philo_nbr < 1 || data->eat_nbr == 0)
		return (-1);
	return (1);
}
