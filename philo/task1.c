/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:20:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/14 18:16:10 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_task(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2);
	while (1)
	{
		if (pickup_forks(philo) < 0)
			break ;
		if (eating(philo) < 0)
			break ;
		if (putdown_forks(philo) < 0)
			break ;
		if (sleeping(philo) < 0)
			break ;
		if (thinking(philo) < 0)
			break ;
		if (is_end(philo))
			break ;
	}
	return (NULL);
}

int	pickup_forks(t_philo *philo)
{
	if (is_end(philo))
		return (-1);
	if (check_leftfork(philo) < 0)
		return (-1);
	if (print_start(philo, TAKEFORKS) < 0)
	{
		thread_kill(philo, 1);
		return (-1);
	}
	if (check_rightfork(philo) < 0)
		return (-1);
	if (print_start(philo, TAKEFORKS) < 0)
	{
		thread_kill(philo, 2);
		return (-1);
	}
	return (0);
}

int	check_leftfork(t_philo *philo)
{
	while (1)
	{
		if (is_end(philo))
			return (-1);
		pthread_mutex_lock(&philo->table->check_mutex);
		if (is_end(philo))
		{
			pthread_mutex_unlock(&philo->table->check_mutex);
			return (-1);
		}
		if (!philo->left_fork->used)
		{
			philo->left_fork->used = USED;
			pthread_mutex_unlock(&philo->table->check_mutex);
			pthread_mutex_lock(&philo->left_fork->fork_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->check_mutex);
		usleep(100);
	}
	return (0);
}

int	check_rightfork(t_philo *philo)
{
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
			pthread_mutex_unlock(&philo->table->check_mutex);
			pthread_mutex_lock(&philo->right_fork->fork_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->check_mutex);
		usleep(100);
	}
	return (0);
}
