/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:01:09 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/13 14:57:21 by yunjcho          ###   ########.fr       */
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

// int	is_dying(t_philo *philo)
// {
// 	unsigned long	print_time;
// 	unsigned long	noteating_time;

// 	print_time = 0;
// 	pthread_mutex_lock(&philo->philo_mutex);
// 	noteating_time = get_printms(philo->lasteat_time);
// 	pthread_mutex_unlock(&philo->philo_mutex);
// 	if (noteating_time > (unsigned long)philo->table->time_to_die)
// 	{
// 		pthread_mutex_lock(&philo->table->table_mutex);
// 		if (!philo->table->is_dying)
// 			philo->table->is_dying = philo->philo_id;
// 		pthread_mutex_unlock(&philo->table->table_mutex);
// 		print_time = get_printms(philo->table->start_time);
// 		pthread_mutex_lock(&philo->table->print_mutex);
// 		printf("%ld %d is died\n", print_time, philo->philo_id);
// 		pthread_mutex_unlock(&philo->table->print_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

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
