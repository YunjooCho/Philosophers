/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:12:15 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/25 19:01:30 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pickup_forks(t_philo *philo)
{
	check_leftfork(philo);
	check_rightfork(philo);
}

void	check_leftfork(t_philo *philo)
{
	sem_wait(philo->table->sem_check); //TODO - sem_philo
	if (is_dying(philo))
	{
		sem_post(philo->table->sem_check); //TODO - sem_philo
		thread_kill(philo);
		exit(1);
	}
	sem_post(philo->table->sem_check); //TODO - sem_philo
	while (1)
	{
		sem_wait(philo->table->sem_check); //TODO - sem_philo
		if (is_dying(philo))
		{
			sem_post(philo->table->sem_check); //TODO - sem_philo
			thread_kill(philo);
			exit(1);
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
				thread_kill(philo);
				exit(1);
			}
			break ;
		}
		sem_post(philo->table->sem_check); //TODO - sem_philo
		usleep(400);
	}
}

int	check_rightfork(t_philo *philo)
{
	sem_wait(philo->table->sem_check); //TODO - sem_philo
	if (is_dying(philo))
	{
		sem_post(philo->table->sem_check); //TODO - sem_philo
		thread_kill(philo);
		return (-1);
	}
	sem_post(philo->table->sem_check); //TODO - sem_philo
	while (1)
	{
		sem_wait(philo->table->sem_check); //TODO - sem_philo
		if (is_dying(philo))
		{
			sem_post(philo->table->sem_check); //TODO - sem_philo
			thread_kill(philo);
			return (-1);
		}
		if (philo->rightfork_cnt == -1)
		{
			sem_post(philo->table->sem_check);
			continue ;
		}
		else if (!philo->rightfork_cnt)
		{
			if (is_dying(philo))
			{
				sem_post(philo->table->sem_check); //TODO - sem_philo
				thread_kill(philo);
				return (-1);
			}
			philo->rightfork_cnt++;
			philo->table->useable_forkcnt--;
			sem_post(philo->table->sem_check);
			sem_wait(philo->table->sem_forks);
			if (print_pickupfork(philo) < 0)
			{
				thread_kill(philo);
				return (-1);
			}
			break ;
		}
		sem_post(philo->table->sem_check);
		usleep(400);
	}
	return (0);
}
