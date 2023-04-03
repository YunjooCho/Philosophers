/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:20:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/03 22:16:43 by yunjcho          ###   ########.fr       */
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
		if(pickup_forks(philo) < 0)
			return (NULL);
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	pickup_forks(t_philo *philo)
{
	unsigned long	pickup_time;

	pickup_time = 0;
	if (thread_kill(philo))
		return (-1);
	// while (1)
	// {
	// 	// if (!check_leftfork(philo))
	// 	// 	print_pickupfork(philo, 1);
	// 	// if (!check_rightfork(philo))
	// 	// 	print_pickupfork(philo, 2);
	// 	if (check_leftfork(philo) < 0)
	// 		return (-1);
	// 	if (check_rightfork(philo) < 0)
	// 		return (-1);
	// 	if (is_pickup(philo))
	// 		break ;
	// 	usleep(400);
	// }
	if (check_leftfork(philo) < 0)
		return (-1);
	if (check_rightfork(philo) < 0)
		return (-1);
	if (thread_kill(philo))
		return (-1);
	return (0);
}

int	is_pickup(t_philo *philo)
{
	int	result;

	result = 0;
	if (!philo->left_fork || !philo->right_fork)
		return (result);
	if (philo->left_fork->fork_user == philo->philo_id \
		&& philo->right_fork->fork_user == philo->philo_id)
		result = 1;
	else
		result = 0;
	return (result);
}

int	check_leftfork(t_philo *philo)
{
	int	result;

	result = 0;
	
	while (1)
	{
		pthread_mutex_lock(&philo->table->check_mutex);
		if (!philo->left_fork->used)
		{
			pthread_mutex_lock(&philo->left_fork->fork_mutex);
			philo->left_fork->used = USED;
			philo->left_fork->fork_user = philo->philo_id;
			// pthread_mutex_unlock(&philo->left_fork->fork_mutex);
			print_pickupfork(philo, 1);
			break ;
		}
		// else
		// 	result = -1;
		pthread_mutex_unlock(&philo->table->check_mutex);
	}
	return (result);
}

int	check_rightfork(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->table->check_mutex);
	while (1)
	{
		if (!philo->right_fork)
			continue ;
		else if (!philo->right_fork->used)
		{
			pthread_mutex_lock(&philo->right_fork->fork_mutex);
			philo->right_fork->used = USED;
			philo->right_fork->fork_user = philo->philo_id;
			// pthread_mutex_unlock(&philo->right_fork->fork_mutex);
			print_pickupfork(philo, 2);
			break ;
		}
		// else
		// 	result = -1;
		pthread_mutex_unlock(&philo->table->check_mutex);
	}
	return (result);
}
