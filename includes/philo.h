/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:10:29 by aaapatou          #+#    #+#             */
/*   Updated: 2021/12/29 02:28:36 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				number;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_nbr;
	int				meals;
	unsigned long	last_meal;
	unsigned long	time_eat;
	struct s_data	*data;
	pthread_mutex_t	*rfork;
	int				fork;
	pthread_mutex_t	*m_display;
	pthread_mutex_t	*m_data;
	pthread_mutex_t	*m_time;
	pthread_mutex_t	*m_death;
	int				forks;
}					t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_nbr;
	int				dead;
	int				satiate;
	int				satiate_nbr;
	unsigned long	start;
	int				death;
	t_philo			*philo;
}					t_data;

// ACTIONS
void			*routine(void *philo);
// INITIALIZING
void			init_philo(t_philo *philo);
void			init_data(t_data *data);
// PARSING
void			ft_read_argument(int ac, char **av, long long *tab);
int				ft_check_argument(int ac, char **av);
int				parse_data(int ac, char **av, t_data *data);
// DISPLAY
int				display_fork(t_philo *philo);
int				display_eating(t_philo *philo, int death);
void			display_sleeping(t_philo *philo);
void			display_death(t_philo *philo);
// UTILS
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_putlongnbr(unsigned long nb);
unsigned long	ft_get_time(void);
void			ft_usleep(unsigned long time);
long long		ft_longatoi(const char *str);
void			data_philo(int i, t_data *data, t_philo *philo);
int				is_someone_dead(t_philo *philo);
void			unlock_forks(t_philo *philo);
int				taking_forks(t_philo *philo);
pthread_mutex_t	*trouver_fork(t_philo *philo);
void			*ft_puterror(char *str);
int				check_satiate(t_philo *philo, int philo_number);
int				is_dead(t_philo *philo);
int				ft_unlock(t_philo *philo, int i);
int				ft_check_meals(t_philo *philo);
// CLEANING
void			ft_clean(t_data *data);
void			*ft_error_malloc(t_philo *philo);

#endif