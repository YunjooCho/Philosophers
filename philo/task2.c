/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:37:29 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/13 10:18:08 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	if (print_start(philo, EATING) < 0)
	{
		thread_kill(philo, 2);
		return (-1);
	}
	if (counting_time(philo, EATING) < 0)
	{
		thread_kill(philo, 2);
		return (-1);
	}
	pthread_mutex_lock(&philo->philo_mutex);
	philo->lasteat_time = get_now();
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (0);
}

int	putdown_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_mutex);
	philo->left_fork->used = NOT_USED;
	philo->right_fork->used = NOT_USED;
	pthread_mutex_unlock(&philo->table->check_mutex);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	// unsigned long print_time = get_printms(philo->table->start_time);
	// pthread_mutex_lock(&philo->table->print_mutex);
	// printf("%ld %d putdown forks\n", print_time, philo->philo_id);
	// pthread_mutex_unlock(&philo->table->print_mutex);
	if (is_end(philo))
		return (-1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (is_end(philo))
		return (-1);
	if (print_start(philo, SLEEPING) < 0)
		return (-1);
	if (counting_time(philo, SLEEPING) < 0)
		return (-1);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (is_end(philo))
		return (-1);
	if (print_start(philo, THINKING) < 0)
		return (-1);
	return (0);
}

int	is_end(t_philo *philo)
{
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
		pthread_mutex_unlock(&philo->table->check_mutex);
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->table->check_mutex);
		philo->left_fork->used = NOT_USED;
		philo->right_fork->used = NOT_USED;
		pthread_mutex_unlock(&philo->table->check_mutex);
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	}
}
