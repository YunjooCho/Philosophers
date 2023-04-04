/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:20:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/04 22:02:51 by yunjcho          ###   ########.fr       */
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
		if (philo->philo_id % 2 == 0)
			usleep(1000);
		if (is_end(philo))
			return (NULL);
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
	}
	return (NULL);
}

int	pickup_forks(t_philo *philo)
{
	unsigned long	pickup_time;

	pickup_time = 0;
	if (check_leftfork(philo) < 0)
		return (-1);
	if (check_rightfork(philo) < 0)
		return (-1);
	return (0);
}

int	check_leftfork(t_philo *philo)
{
	if (is_end(philo))
		return (-1);
	while (1)
	{
		if (is_end(philo))
		{
			thread_kill(philo, 1);
			return (-1);
		}
		pthread_mutex_lock(&philo->table->check_mutex);
		if (!philo->left_fork->used)
		{
			philo->left_fork->used = USED;
			philo->left_fork->fork_user = philo->philo_id;
			pthread_mutex_lock(&philo->left_fork->fork_mutex);
			pthread_mutex_unlock(&philo->table->check_mutex);
			print_pickupfork(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->table->check_mutex);
		usleep(400);
	}
	return (0);
}

int	check_rightfork(t_philo *philo)
{
	if (is_end(philo))
	{
		thread_kill(philo, 1);
		return (-1);
	}
	while (1)
	{
		if (is_end(philo))
		{
			thread_kill(philo, 1);
			return (-1);
		}
		pthread_mutex_lock(&philo->table->check_mutex);
		if (!philo->right_fork)
		{
			pthread_mutex_unlock(&philo->table->check_mutex);
			continue ;
		}
		else if (!philo->right_fork->used)
		{
			philo->right_fork->used = USED;
			philo->right_fork->fork_user = philo->philo_id;
			pthread_mutex_lock(&philo->right_fork->fork_mutex);
			pthread_mutex_unlock(&philo->table->check_mutex);
			print_pickupfork(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->table->check_mutex);
		usleep(400);
	}
	return (0);
}
