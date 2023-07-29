/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:47:29 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/29 21:54:48 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dying(t_philo *philo)
{
	unsigned long	print_time;
	unsigned long	noeating_time;

	print_time = 0;
	noeating_time = 0;
	noeating_time = get_printms(philo->lasteat_time);
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

int	check_eatcnt(t_philo *philo)
{
	if (philo->table->must_eat_cnt != -1 && \
		philo->eat_cnt == philo->table->must_eat_cnt)
	{
		sem_post(philo->table->sem_check);
		//Debugging
		// sem_wait(philo->table->sem_check);
		printf("philo id : %d is over eating, over count : %d\n", philo->philo_id, philo->eat_cnt);
		// sem_post(philo->table->sem_check);
		return (1);
	}
	return (0);
}

void	process_kill(t_philo *philo)
{
	// sem_wait(philo->table->sem_check);
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
	// sem_post(philo->table->sem_check);
}
