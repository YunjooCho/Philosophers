/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:20:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/04 17:35:40 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_task(void *argument)
{
	t_philo	*philo;

	philo = NULL;
	philo = (void *)argument;
	while (1)
	{
		if (thread_kill(philo))
			return (NULL);
		if (philo->philo_id % 2 == 0)
			usleep(1000);
		if (pickup_forks(philo) < 0)
			return (NULL);
		if (eating(philo) < 0)
			return (NULL);
		if (putdown_forks(philo) < 0)
			return (NULL);
		if (sleeping(philo) < 0)
			return (NULL);
		if (thinking(philo) < 0)
			return (NULL);
		usleep(400);
	}
	return (NULL);
}

int	pickup_forks(t_philo *philo)
{
	unsigned long	pickup_time;

	pickup_time = 0;
	if (thread_kill(philo))
		return (-1);
	if (check_leftfork(philo) < 0)
		return (-1);
	if (check_rightfork(philo) < 0)
		return (-1);
	if (thread_kill(philo))
		return (-1);
	return (0);
}

int	check_leftfork(t_philo *philo)
{
	if (thread_kill(philo))
		return (-1);
	while (1)
	{
		if (thread_kill(philo))
			return (-1);
		pthread_mutex_lock(&philo->table->check_mutex);
		if (!philo->left_fork->used)
		{
			pthread_mutex_lock(&philo->left_fork->fork_mutex);
			philo->left_fork->used = USED;
			philo->left_fork->fork_user = philo->philo_id;
			if (print_pickupfork(philo, 1) < 0)
				return (-1);
			pthread_mutex_unlock(&philo->table->check_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->check_mutex);
		usleep(400);
	}
	return (0);
}

int	check_rightfork(t_philo *philo)
{
	if (thread_kill(philo))
		return (-1);
	while (1)
	{
		if (thread_kill(philo))
			return (-1);
		pthread_mutex_lock(&philo->table->check_mutex);
		if (!philo->right_fork)
		{
			pthread_mutex_unlock(&philo->table->check_mutex);
			continue ;
		}
		else if (!philo->right_fork->used)
		{
			pthread_mutex_lock(&philo->right_fork->fork_mutex);
			philo->right_fork->used = USED;
			philo->right_fork->fork_user = philo->philo_id;
			if (print_pickupfork(philo, 2) < 0)
				return (-1);
			pthread_mutex_unlock(&philo->table->check_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->check_mutex);
		usleep(400);
	}
	return (0);
}
