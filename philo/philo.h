/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:08:48 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/03 17:01:24 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define USED 1
# define NOT_USED 0

typedef struct s_table
{
	int				philo_cnt;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_cnt;
	unsigned long	start_time;
	struct s_philo	*philos;
	struct s_fork	*forks;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	table_mutex;
	int				is_dying;
}	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				used;
	int				fork_user;
}	t_fork;

typedef struct s_philo
{
	int				philo_id;
	int				eat_cnt;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_table			*table;
	unsigned long	lasteat_time;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	int				checked;
}	t_philo;

int				init_table(char **av, t_table *table);
int				is_digit(int c);
int				is_plus_minus(char *str, int idx);
int				check_operators(char *str, int idx);
int				ph_atoi(char *str);
void			translate_aton(char **av, t_table *table);
t_philo			*malloc_philosarr(t_table *table);
int				init_philo(t_philo *philo, t_table *table, int idx);
t_fork			*malloc_forksarr(int forks_cnt);
int				create_forkmutexs(t_fork *fork);
unsigned long	get_now(void);
unsigned long	get_printms(unsigned long start_time);
int				create_threads(t_table *table);
int				monitoring(t_table *table);
int				is_dying(t_table *table, int idx);
int				is_musteat(t_table *table, int idx, int *alleat_cnt);
int				threads_detach(t_table *table);
void			*philo_task(void *argument);
int				pickup_forks(t_philo *philo);
void			print_pickupfork(t_philo *philo, int flag);
int				check_leftfork(t_philo *philo);
int				check_rightfork(t_philo *philo);
int				is_pickup(t_philo *philo);
void			eating(t_philo *philo);
void			putdown_forks(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
int				print_error(char *str);
void			print_table(t_table *table);
void			print_forks(int cnt, t_fork *forks);
void			print_philos(int cnt, t_philo *philos);

#endif