/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:11:02 by rasaboun          #+#    #+#             */
/*   Updated: 2022/01/24 19:18:56 by rasaboun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_ph
{
	pthread_t		thread;
	int				index;
	int				dtime;
	int				etime;
	int				stime;
	int				sat_eat;
	int				meal_num;
	unsigned long	last_meal;
	struct s_core	*core;
	pthread_mutex_t	*r_fork;
	int				fork;
	pthread_mutex_t	*m_display;
	pthread_mutex_t	*m_core;
	pthread_mutex_t	*m_time;
	pthread_mutex_t	*m_death;
	int				forks;
}					t_ph;

typedef struct s_core
{
	int				philo_nbr;
	int				dtime;
	int				etime;
	int				stime;
	int				sat_eat;
	int				dead;
	int				satiate;
	int				satiate_nbr;
	unsigned long	start;
	int				death;
	struct s_ph		*philo;
}					t_core;

void			ft_putstr_fd(char *s, int fd);
long			ft_latoi(const char *str);
int				ft_isdigit(int c);
int				check_arg(int ac, char **av);
int				core_init(int ac, char **av, t_core *core);
t_ph			*philo_init(t_core *core, t_ph *philo);
void			init_philo(t_core *core, t_ph *philo);
unsigned long	get_time(void);
void			errmalloc(t_ph *philo);
int				give_forks(int ph_nbr, t_ph *philo);
void			start_threads(t_core *core);
void			ft_putlnbr(unsigned long nb);
void			ft_putchar(char c);
int				print_fork(t_ph *philo);
int				print_eating(t_ph *philo, int death);
void			print_sleeping(t_ph *philo);
void			print_death(t_ph *philo);
pthread_mutex_t	*find_fork(t_ph *philo);
void			ft_usleep(unsigned long time);
int				unlock_all(t_ph *philo, int i);
int				check_eat(t_ph *philo);
int				is_dead(t_ph *philo);
int				is_one_dead(t_ph *philo);
void			ft_eat(t_ph *philo);
void			ft_sleep(t_ph *philo);
void			ft_think(t_ph *philo);
int				ft_take_forks(t_ph *philo);
void			clean_philo(t_core *core);
int				check_satiate(t_ph *philo, int philo_number);
int				taking_fork(t_ph *philo);
int				get_data(int ac, char **av, t_core *core);
#endif