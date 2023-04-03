/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:43 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/03 17:12:30 by yunjcho          ###   ########.fr       */
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

#endif