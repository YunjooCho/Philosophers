/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:43 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/05 05:56:11 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <signal.h>

# define USED 1
# define NOT_USED 0
# define FORK_CNT 2

typedef struct s_table
{
	int				philo_cnt;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_cnt;
	unsigned long	start_time;
	struct s_philo	*philos;
	sem_t			*sem_forks;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	table_mutex;
	int				is_dying;
}	t_table;

typedef struct s_philo
{
	pid_t			pid;
	int				philo_id;
	int				eat_cnt;
	int				fork_cnt;
	t_table			*table;
	unsigned long	lasteat_time;
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
unsigned long	get_now(void);
unsigned long	get_printms(unsigned long start_time);
int				create_process(t_table *table);
void			parent_proc(t_philo *philo, int *pid);
void			children_proc(t_philo *philo);
int				pickup_forks(t_philo *philo);
int				eating(t_philo *philo);
int				putdown_forks(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);
int				is_dying(t_philo *philo);
int				print_error(char *str);
void			print_table(t_table *table);
void			print_philos(int cnt, t_philo *philos);

#endif