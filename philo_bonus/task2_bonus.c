/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:19:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/06 21:01:29 by yunjcho          ###   ########.fr       */
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
		thread_kill(philo, 2);
		return (-1);
	}
	while (1)
	{
		if (is_end(philo))
		{
			thread_kill(philo, 2);
			return (-1);
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
	sem_post(philo->table->sem_check);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	if (is_end(philo))
		return (-1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	unsigned long	sleepstart_time;
	unsigned long	sleeping_time;
	unsigned long	print_time;

	sleeping_time = 0;
	sleepstart_time = get_now();
	if (is_end(philo))
		return (-1);
	sem_wait(philo->table->sem_print);
	print_time = get_printms(philo->table->start_time);
	if (is_end(philo))
	{
		sem_post(philo->table->sem_print);
		return (-1);
	}
	printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	sem_post(philo->table->sem_print);
	while (1)
	{
		if (is_end(philo))
			return (-1);
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

	if (is_end(philo))
		return (-1);
	sem_wait(philo->table->sem_print);
	print_time = get_printms(philo->table->start_time);
	if (is_end(philo))
	{
		sem_post(philo->table->sem_print);
		return (-1);
	}
	printf("%ld %d is thinking\n", print_time, philo->philo_id);
	sem_post(philo->table->sem_print);
	return (0);
}

int	is_end(t_philo *philo)
{
	int	idx;

	idx = 0;
	sem_wait(philo->table->sem_print);
	if (philo->table->is_dying)
	{
		sem_post(philo->table->sem_print);
		return (1);
	}
	sem_post(philo->table->sem_print);
	return (0);
}

void	thread_kill(t_philo *philo, int flag)
{
	if (flag == 1)
	{
		sem_wait(philo->table->sem_check);
		philo->leftfork_cnt--;
		sem_post(philo->table->sem_check);
		sem_post(philo->table->sem_forks);
	}
	else
	{
		sem_wait(philo->table->sem_check);
		philo->leftfork_cnt--;
		philo->rightfork_cnt--;
		sem_post(philo->table->sem_check);
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_forks);
	}
}
