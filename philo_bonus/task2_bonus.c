/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:19:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/13 19:52:46 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating(t_philo *philo)
{
	unsigned long	eatstart_time;
	unsigned long	eating_time;

	eating_time = 0;
	eatstart_time = get_now();
	if (print_starteat(philo) < 0)
	{
		thread_kill(philo);
		exit(1);
	}
	while (1)
	{
		if (is_dying(philo))
		{
			thread_kill(philo);
			exit(1);
		}
		eating_time = get_printms(eatstart_time);
		if (eating_time >= (unsigned long)philo->table->time_to_eat)
		{
			sem_wait(philo->table->sem_check);
			philo->lasteat_time = get_now();
			philo->eat_cnt++;
			sem_post(philo->table->sem_check);
			break ;
		}
		usleep(400);
	}
	return (0);
}

int	putdown_forks(t_philo *philo)
{
	sem_wait(philo->table->sem_check);
	philo->leftfork_cnt--;
	philo->rightfork_cnt--;
	philo->table->useable_forkcnt += 2;
	sem_post(philo->table->sem_check);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	if (is_dying(philo))
		exit(1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	unsigned long	sleepstart_time;
	unsigned long	sleeping_time;
	unsigned long	print_time;

	sleeping_time = 0;
	sleepstart_time = get_now();
	if (is_dying(philo))
		exit(1);
	sem_wait(philo->table->sem_print);
	print_time = get_printms(philo->table->start_time);
	if (is_dying(philo))
	{
		sem_post(philo->table->sem_print);
		exit(1);
	}
	printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	sem_post(philo->table->sem_print);
	while (1)
	{
		if (is_dying(philo))
			exit(1);
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

	if (is_dying(philo))
		exit(1);
	sem_wait(philo->table->sem_print);
	print_time = get_printms(philo->table->start_time);
	if (is_dying(philo))
	{
		sem_post(philo->table->sem_print);
		exit(1);
	}
	printf("%ld %d is thinking\n", print_time, philo->philo_id);
	sem_post(philo->table->sem_print);
	return (0);
}

int	is_dying(t_philo *philo)
{
	unsigned long	print_time;
	unsigned long	noeating_time;

	print_time = 0;
	noeating_time = 0;
	sem_wait(philo->table->sem_check);
	noeating_time = get_printms(philo->lasteat_time);
	sem_post(philo->table->sem_check);
	if (noeating_time > (unsigned long)philo->table->time_to_die)
	{
		print_time = get_printms(philo->table->start_time);
		sem_wait(philo->table->sem_print);
		printf("%ld %d is died\n", print_time, philo->philo_id);
		sem_post(philo->table->sem_print);
		return (1);
	}
	return (0);
}

void	thread_kill(t_philo *philo)
{
	sem_wait(philo->table->sem_check);
	if (philo->leftfork_cnt)
	{
		philo->leftfork_cnt--;
		sem_post(philo->table->sem_forks);
		philo->table->useable_forkcnt++;
	}
	if (philo->rightfork_cnt)
	{
		philo->rightfork_cnt--;
		sem_post(philo->table->sem_forks);
		philo->table->useable_forkcnt++;
	}
	sem_post(philo->table->sem_check);
}
