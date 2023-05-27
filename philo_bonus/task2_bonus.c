/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:19:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/27 20:26:39 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating(t_philo *philo)
{
	if (print_start(philo, EATING) < 0)
	{
		thread_kill(philo);
		exit(1);
	}
	if (counting_time(philo, EATING) < 0)
	{
		thread_kill(philo);
		exit(1);
	}
	sem_wait(philo->table->sem_check);
	philo->lasteat_time = get_now();
	philo->eat_cnt++;
	sem_post(philo->table->sem_check);
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
	sem_wait(philo->table->sem_check);
	if (is_dying(philo) || check_eatcnt(philo))
	{
		// sem_post(philo->table->sem_check);
		exit(1);
	}
	sem_post(philo->table->sem_check);
	return (0);
}

int	sleeping(t_philo *philo)
{
	sem_wait(philo->table->sem_check);
	if (is_dying(philo))
	{
		// sem_post(philo->table->sem_check);
		exit(1);
	}
	sem_post(philo->table->sem_check);
	if (print_start(philo, SLEEPING) < 0)
		exit(1);
	if (counting_time(philo, SLEEPING) < 0)
		exit(1);
	return (0);
}

int	thinking(t_philo *philo)
{
	sem_wait(philo->table->sem_check);
	if (is_dying(philo))
	{
		// sem_post(philo->table->sem_check);
		exit(1);
	}
	sem_post(philo->table->sem_check);
	if (print_start(philo, THINKING) < 0)
		exit(1);
	return (0);
}
