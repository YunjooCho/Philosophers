/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:37:29 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/14 18:44:36 by yunjcho          ###   ########.fr       */
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
