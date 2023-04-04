/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:43 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/05 00:11:40 by yunjcho          ###   ########.fr       */
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
int				init_philo(t_philo *philo, t_table *table, int idx, pid_t *pid);

void			parent_proc(t_table *table, t_philo *philos_arr, int idx, pid_t *pid);
void			children_proc(void);

int				print_error(char *str);
void			print_table(t_table *table);
void			print_philos(int cnt, t_philo *philos);

#endif