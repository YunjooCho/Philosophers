/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:20:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/03 16:03:54 by yunjcho          ###   ########.fr       */
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
		pickup_forks(philo);
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	pickup_forks(t_philo *philo)
{
	int				result;
	unsigned long	pickup_time;

	result = 0;
	pickup_time = 0;
	while (1)
	{
		if (!check_leftfork(philo))
			print_pickupfork(philo, 1);
		if (!check_rightfork(philo))
			print_pickupfork(philo, 2);
		if (is_pickup(philo))
			break ;
		usleep(400);
	}
	return (result);
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

void	print_pickupfork(t_philo *philo, int flag)
{
	unsigned long	pickup_time;

	pickup_time = 0;
	pickup_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	if (flag == 1)
	{
		printf("%ld %d has taken a fork\n", \
			pickup_time, philo->philo_id);
	}
	else
	{
		printf("%ld %d has taken a fork\n", \
			pickup_time, philo->philo_id);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}

int	check_leftfork(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->table->check_mutex);
	if (!philo->left_fork->used)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		philo->left_fork->used = USED;
		philo->left_fork->fork_user = philo->philo_id;
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	}
	else
		result = -1;
	pthread_mutex_unlock(&philo->table->check_mutex);
	return (result);
}

int	check_rightfork(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->table->check_mutex);
	if (!philo->right_fork)
		usleep(1000);
	else if (!philo->right_fork->used)
	{
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		philo->right_fork->used = USED;
		philo->right_fork->fork_user = philo->philo_id;
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	}
	else
		result = -1;
	pthread_mutex_unlock(&philo->table->check_mutex);
	return (result);
}
