/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:12:15 by yunjcho           #+#    #+#             */
/*   Updated: 2023/08/05 16:16:50 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pickup_forks(t_philo *philo)
{
	check_leftfork(philo);
	if (print_start(philo, TAKEFORKS) < 0)
	{
		process_kill(philo);
		exit(EXIT_FAILURE);
	}
	check_rightfork(philo);
	if (print_start(philo, TAKEFORKS) < 0)
	{
		process_kill(philo);
		exit(EXIT_FAILURE);
	}
}

void	check_leftfork(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->table->sem_check);
		if (is_dying(philo))
		{
			// sem_post(philo->table->sem_check);
			process_kill(philo);
			exit(EXIT_FAILURE);
		}
		if (!philo->table->useable_forkcnt)
		{
			sem_post(philo->table->sem_check);
			continue ;
		}
		if (!philo->leftfork_cnt)
		{
			philo->leftfork_cnt++;
			philo->table->useable_forkcnt--;
			sem_post(philo->table->sem_check);
			sem_wait(philo->table->sem_forks);
			return ;
		}
		sem_post(philo->table->sem_check);
		usleep(100);
	}
}

void	check_rightfork(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->table->sem_check);
		if (is_dying(philo))
		{
			// sem_post(philo->table->sem_check);
			process_kill(philo);
			exit(EXIT_FAILURE);
		}
		if (philo->rightfork_cnt == -1)
		{
			sem_post(philo->table->sem_check);
			continue ;
		}
		else if (!philo->rightfork_cnt)
		{
			philo->rightfork_cnt++;
			philo->table->useable_forkcnt--;
			sem_post(philo->table->sem_check);
			sem_wait(philo->table->sem_forks);
			return ;
		}
		sem_post(philo->table->sem_check);
		usleep(100);
	}
}
