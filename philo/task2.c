/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:37:29 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/04 21:33:26 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	unsigned long	eatstart_time;
	unsigned long	eating_time;

	eating_time = 0;
	eatstart_time = get_now();
	if (is_end(philo))
	{
		thread_kill(philo, 3);
		return (-1);
	}
	print_starteat(philo);
	while (1)
	{
		eating_time = get_printms(eatstart_time);
		if (eating_time >= (unsigned long)philo->table->time_to_eat)
		{
			pthread_mutex_lock(&philo->philo_mutex);
			philo->lasteat_time = get_now();
			philo->eat_cnt++;
			pthread_mutex_unlock(&philo->philo_mutex);
			break ;
		}
		usleep(400);
	}
	return (0);
}

int	putdown_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_mutex);
	if (philo->left_fork->used)
	{
		philo->left_fork->used = NOT_USED;
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	}
	pthread_mutex_unlock(&philo->table->check_mutex);
	pthread_mutex_lock(&philo->table->check_mutex);
	if (philo->right_fork->used)
	{
		philo->right_fork->used = NOT_USED;
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	}
	pthread_mutex_unlock(&philo->table->check_mutex);
	return (0);
}

int	sleeping(t_philo *philo)
{
	unsigned long	sleepstart_time;
	unsigned long	sleeping_time;
	unsigned long	print_time;

	sleeping_time = 0;
	sleepstart_time = get_now();
	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	if (is_end(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (-1);
	}
	printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	while (1)
	{
		sleeping_time = get_printms(sleepstart_time);
		if (sleeping_time >= (unsigned long)philo->table->time_to_sleep)
			break ;
		usleep(400);
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	unsigned long	print_time;

	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	if (is_end(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (-1);
	}
	printf("%ld %d is thinking\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}

int	is_end(t_philo *philo)
{
	int	idx;

	idx = 0;
	pthread_mutex_lock(&philo->table->table_mutex);
	if (philo->table->is_dying)
	{
		pthread_mutex_unlock(&philo->table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->table_mutex);
	return (0);
}

void	thread_kill(t_philo *philo, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(&philo->table->check_mutex);
		philo->left_fork->used = NOT_USED;
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		pthread_mutex_unlock(&philo->table->check_mutex);
	}
	else if (flag == 2)
	{
		pthread_mutex_lock(&philo->table->check_mutex);
		philo->left_fork->used = NOT_USED;
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		philo->right_fork->used = NOT_USED;
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		pthread_mutex_unlock(&philo->table->check_mutex);
	}
}
