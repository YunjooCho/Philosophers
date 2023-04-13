/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:01:09 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/13 13:01:30 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
