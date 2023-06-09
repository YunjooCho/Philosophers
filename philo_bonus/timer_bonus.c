/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:06:40 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/27 19:47:06 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long	get_now(void)
{
	struct timeval	now;
	unsigned long	now_time;

	now_time = 0;
	gettimeofday(&now, NULL);
	now_time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (now_time);
}

unsigned long	get_printms(unsigned long start_time)
{
	unsigned long	end_time;
	unsigned long	diff_time;

	end_time = get_now();
	diff_time = end_time - start_time;
	return (diff_time);
}

void	ft_usleep(unsigned long target_time)
{
	unsigned long	t1;
	unsigned long	t2;

	t1 = get_now();
	t2 = t1;
	while (t1 - t2 + 1 <= target_time)
	{
		usleep(100);
		t1 = get_now();
	}
}

int	counting_time(t_philo *philo, int flag)
{
	unsigned long	t1;
	unsigned long	t2;
	unsigned long	target_time;

	t1 = get_now();
	t2 = t1;
	target_time = 0;
	sem_wait(philo->table->sem_check);
	if (is_dying(philo))
	{
		// sem_post(philo->table->sem_check);
		return (-1);
	}
	sem_post(philo->table->sem_check);
	if (flag == EATING)
		target_time = (unsigned long)philo->table->time_to_eat;
	else if (flag == SLEEPING)
		target_time = (unsigned long)philo->table->time_to_sleep;
	while (t1 - t2 + 1 <= target_time)
	{
		usleep(100);
		sem_wait(philo->table->sem_check);
		if (is_dying(philo))
		{
			// sem_post(philo->table->sem_check);
			return (-1);
		}
		sem_post(philo->table->sem_check);
		t1 = get_now();
	}
	return (0);
}
