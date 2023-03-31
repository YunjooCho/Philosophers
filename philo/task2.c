/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:37:29 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/31 17:00:51 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	unsigned long	eatstart_time;
	unsigned long	eating_time;
	unsigned long	print_time;

	eating_time = 0;
	eatstart_time = get_now();
	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is eating\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	while (1)
	{
		eating_time = get_printms(eatstart_time);
		if (eating_time >= (unsigned long)philo->table->time_to_eat)
		{
			pthread_mutex_lock(&philo->philo_mutex);
			philo->lasteat_time = get_now();
			philo->eat_cnt++;
			pthread_mutex_unlock(&philo->philo_mutex);
			// //TODO - Debugging
			// unsigned long	eatend_time = 0;
			// pthread_mutex_lock(&philo->table->print_mutex);
			// eatend_time = get_printms(philo->table->start_time);
			// printf("%ld %d eating over\n", eatend_time, philo->philo_id);
			// pthread_mutex_unlock(&philo->table->print_mutex);
			// //TODO - Debugging
			break ;
		}
		usleep(400);
	}
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_mutex);
	if (philo->left_fork->used)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		philo->left_fork->used = NOT_USED;
		// //TODO - Debugging
		// unsigned long	putdown_time;
		// putdown_time = get_printms(philo->table->start_time);
		// pthread_mutex_lock(&philo->table->print_mutex);
		// printf("%ld %d putdown a left fork\n", putdown_time, philo->philo_id);
		// pthread_mutex_unlock(&philo->table->print_mutex);
		// //TODO - Debugging
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	}
	pthread_mutex_unlock(&philo->table->check_mutex);
	pthread_mutex_lock(&philo->table->check_mutex);
	if (philo->right_fork->used)
	{
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		philo->right_fork->used = NOT_USED;
		// //TODO - Debugging
		// unsigned long	putdown_time;
		// putdown_time = get_printms(philo->table->start_time);
		// pthread_mutex_lock(&philo->table->print_mutex);
		// printf("%ld %d putdown a right fork\n", putdown_time, philo->philo_id);
		// pthread_mutex_unlock(&philo->table->print_mutex);
		// //TODO - Debugging
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	}
	pthread_mutex_unlock(&philo->table->check_mutex);
}

void	sleeping(t_philo *philo)
{
	unsigned long	sleepstart_time;
	unsigned long	sleeping_time;
	unsigned long	print_time;

	sleepstart_time = get_now();
	sleeping_time = 0;
	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	while (1)
	{
		usleep(400);
		sleeping_time = get_printms(sleepstart_time);
		if (sleeping_time >= (unsigned long)philo->table->time_to_sleep)
		{
			// //TODO - Debugging
			// unsigned long	sleepend_time = 0;
			// pthread_mutex_lock(&philo->table->print_mutex);
			// sleepend_time = get_printms(philo->table->start_time);
			// printf("%ld %d sleeping over\n", sleepend_time, philo->philo_id);
			// pthread_mutex_unlock(&philo->table->print_mutex);
			// //TODO - Debugging
			break ;
		}
	}
}

void	thinking(t_philo *philo)
{
	unsigned long	print_time;

	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is thinking\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}