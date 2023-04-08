/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:43 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/08 21:25:37 by yunjcho          ###   ########.fr       */
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
	int				useable_forkcnt;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_cnt;
	unsigned long	start_time;
	struct s_philo	*philos;
	const char		*sem_forksname;
	const char		*sem_checkname;
	const char		*sem_printname;
	const char		*sem_tablename;
	sem_t			*sem_forks;
	sem_t			*sem_check;
	sem_t			*sem_print;
	sem_t			*sem_table;
	int				is_dying;
}	t_table;

typedef struct s_philo
{
	pid_t			pid;
	int				philo_id;
	int				eat_cnt;
	int				leftfork_cnt;
	int				rightfork_cnt;
	t_table			*table;
	unsigned long	lasteat_time;
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
int				is_end(t_philo *philo);
void			thread_kill(t_philo *philo, int flag);
int				create_process(t_table *table);
int				monitoring(t_table *table);
int				is_dying(t_table *table, int idx);
int				is_musteat(t_table *table, int idx, int *alleat_cnt);
void			wait_processes(int len);
void			philo_task(t_philo *philo);
int				pickup_forks(t_philo *philo);
int				check_leftfork(t_philo *philo);
int				check_rightfork(t_philo *philo);
int				eating(t_philo *philo);
int				putdown_forks(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);
int				print_error(char *str);
int				print_pickupfork(t_philo *philo);
int				print_starteat(t_philo *philo);
void			print_table(t_table *table);
void			print_philos(int cnt, t_philo *philos);

#endif