/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:12:15 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/08 21:27:52 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pickup_forks(t_philo *philo)
{
	if (check_leftfork(philo) < 0)
		return (-1);
	if (check_rightfork(philo) < 0)
		return (-1);
	return (0);
}

int	check_leftfork(t_philo *philo)
{
	if (is_end(philo))
		return (-1);
	while (1)
	{
		sem_wait(philo->table->sem_check); //TODO - sem_philo
		if (is_end(philo))
		{
			sem_post(philo->table->sem_check); //TODO - sem_philo
			return (-1);
		}
		if (!philo->table->useable_forkcnt)
		{
			sem_post(philo->table->sem_check); //TODO - sem_philo
			continue ;
		}
		if (!philo->leftfork_cnt)
		{
			philo->leftfork_cnt++;
			philo->table->useable_forkcnt--;
			sem_post(philo->table->sem_check); //TODO - sem_philo
			sem_wait(philo->table->sem_forks);
			if (print_pickupfork(philo) < 0)
			{
				thread_kill(philo, 1);
				return (-1);
			}
			break ;
		}
		sem_post(philo->table->sem_check);
		usleep(400);
	}
	return (0);
}

int	check_rightfork(t_philo *philo)
{
	if (is_end(philo))
	{
		thread_kill(philo, 1);
		return (-1);
	}
	while (1)
	{
		if (is_end(philo))
		{
			thread_kill(philo, 1);
			return (-1);
		}
		sem_wait(philo->table->sem_check);
		if (philo->rightfork_cnt == -1)
		{
			sem_post(philo->table->sem_check);
			continue ;
		}
		else if (!philo->rightfork_cnt)
		{
			if (is_end(philo))
			{
				sem_post(philo->table->sem_check);
				return (-1);
			}
			philo->rightfork_cnt++;
			philo->table->useable_forkcnt--;
			sem_post(philo->table->sem_check);
			sem_wait(philo->table->sem_forks);
			if (print_pickupfork(philo) < 0)
			{
				thread_kill(philo, 2);
				return (-1);
			}
			break ;
		}
		sem_post(philo->table->sem_check);
		usleep(400);
	}
	return (0);
}