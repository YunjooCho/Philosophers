/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:43 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/27 18:13:51 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

# define USED 1
# define NOT_USED 0
# define FORK_CNT 2

# define TAKEFORKS 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4

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
	sem_t			*sem_forks;
	sem_t			*sem_check;
	sem_t			*sem_print;
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
	int				is_dying;
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
void			ft_usleep(unsigned long target_time);
int				is_dying(t_philo *philo);
void			thread_kill(t_philo *philo);
int				create_process(t_table *table);
void			wait_processes(t_table *table);
void			philo_task(t_philo *philo);
void			pickup_forks(t_philo *philo);
void			check_leftfork(t_philo *philo);
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