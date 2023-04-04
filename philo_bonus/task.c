/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:12:15 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/05 05:53:03 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pickup_forks(t_philo *philo)
{
	unsigned long	pickup_time;

	pickup_time = 0;
	while (1)
	{
		if (philo->fork_cnt == FORK_CNT)
			break;
		sem_wait(philo->table->sem_forks);
		pickup_time = get_printms(philo->table->start_time);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d has taken a fork\n", \
		pickup_time, philo->philo_id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		philo->fork_cnt++;
	}
	return (0);
}

int	eating(t_philo *philo)
{
	unsigned long	eating_time;
	unsigned long	eatstart_time;
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
			philo->lasteat_time = get_now();
			philo->eat_cnt++;
			break ;
		}
		usleep(400);
	}
	return (0);
}

int	putdown_forks(t_philo *philo)
{
	while (1)
	{
		if (philo->fork_cnt == 0)
			break ;
		sem_post(philo->table->sem_forks);
		philo->fork_cnt--;
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	unsigned long	sleeping_time;
	unsigned long	sleepstart_time;
	unsigned long	print_time;

	sleeping_time = 0;
	sleepstart_time = get_now();
	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	while (1)
	{
		sleeping_time = get_printms(sleepstart_time);
		if (sleeping_time >= (unsigned long)philo->table->time_to_sleep)
			break ;
		usleep(400);
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	unsigned long	print_time;

	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is thinking\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}

int	is_dying(t_philo *philo)
{
	unsigned long	noteating_time;

	noteating_time = 0;
	while (1)
	{
		noteating_time = get_printms(philo->lasteat_time);
		if (noteating_time >= (unsigned long)philo->table->time_to_eat)
			return (1);
		usleep(400);
	}
	return (0);
}