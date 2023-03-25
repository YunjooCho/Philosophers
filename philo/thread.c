/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:09:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/25 23:24:50 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philothreads(t_table *table, t_philo **philos, t_fork **forks)
{
	long			idx;
	int				result;
	pthread_mutex_t mutex;
	
	(void)forks;
	idx = 0;
	result = pthread_mutex_init(&mutex, NULL);
	if (result == -1)
	{
		printf("Mutex Init Error\n");
		return (result);
	}
	result = 0;
	while (idx < table->philo_cnt)
	{
		result = pthread_create(&philos[idx]->thread, NULL, task, (void *)idx);
		// table->cur_idx = idx;
		// result = pthread_create(&philos[idx]->thread, NULL, philo_task, (void *)table);
		if (result < 0)
			return (-1);
		idx++;
	}
	return (0);
}

void	*task(void *idx_back)
{
	struct timeval	cur_time;
	long			philo_id;
	
	philo_id = (long)idx_back;
	if (gettimeofday(&cur_time, NULL) == -1)
	{
		printf("gettimeofday() Fail\n");
		return (NULL);
	}
	printf("[%d] %ld has taken a fork\n", cur_time.tv_usec, philo_id + 1);
	printf("[%d] %ld is eating\n", cur_time.tv_usec, philo_id + 1);
	printf("[%d] %ld is sleeping\n", cur_time.tv_usec, philo_id + 1);
	printf("[%d] %ld is thinking\n", cur_time.tv_usec, philo_id + 1);
	printf("[%d] %ld died\n", cur_time.tv_usec, philo_id + 1);
	usleep(10);
	pthread_exit(0);
	return (NULL);
}

void	*philo_task(void *info)
{
	t_table			*table;
	struct timeval	cur_time;
	
	
	table = NULL;
	table = (t_table *)info;
	if (gettimeofday(&cur_time, NULL) == -1)
	{
		printf("gettimeofday() Fail\n");
		return (NULL);
	}
	pickup_forks(table);
	printf("[%d] %ld has taken a fork\n", cur_time.tv_usec, table->cur_idx + 1);
	printf("[%d] %ld is eating\n", cur_time.tv_usec, table->cur_idx + 1);
	printf("[%d] %ld is sleeping\n", cur_time.tv_usec, table->cur_idx + 1);
	printf("[%d] %ld is thinking\n", cur_time.tv_usec, table->cur_idx + 1);
	printf("[%d] %ld died\n", cur_time.tv_usec, table->cur_idx + 1);
	usleep(10);
	pthread_exit(0);
	// eating();
	// putdown_forks();
	// sleeping();
	// tinkking();
	return (NULL);
}

void	pickup_forks(t_table *table)
{
	(void)table;
	printf("-------------- test print -----------------\n");
}

// void	ft_usleep(int time)
// {
// }

// void	get_milSec(long millisec)
// {
// 	int	result;
// 	int	seconds;
// 	int	minutes;
// 	int	hours;
// 	int	day;
// 	int	month;
// 	int year;

// 	result = 0;
// 	seconds = 0;
// 	minutes = 0;
// 	hours = 0;
// 	day = 0;
// 	month = 0;
// 	year = 0;

// 	result = millisec % 1000;
// }
