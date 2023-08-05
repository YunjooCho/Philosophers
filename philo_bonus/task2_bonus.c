/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:19:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/08/05 16:18:18 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating(t_philo *philo)
{
	if (print_start(philo, EATING) < 0)
	{
		process_kill(philo);
		exit(EXIT_FAILURE);
	}
	if (counting_time(philo, EATING) < 0)
	{
		process_kill(philo);
		exit(EXIT_FAILURE);
	}
	sem_wait(philo->table->sem_check);
	philo->lasteat_time = get_now();
	philo->eat_cnt++;
	
	//Debugging
	// printf("philo id : %d eat count : %d\n", philo->philo_id, philo->eat_cnt);

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
	if (check_eatcnt(philo))
	{
		// sem_post(philo->table->sem_check);
		exit(EXIT_SUCCESS);
	}
	if (is_dying(philo))
	{
		// sem_post(philo->table->sem_check);
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	sem_post(philo->table->sem_check);
	if (print_start(philo, SLEEPING) < 0)
		exit(EXIT_FAILURE);
	if (counting_time(philo, SLEEPING) < 0)
		exit(EXIT_FAILURE);
	return (0);
}

int	thinking(t_philo *philo)
{
	sem_wait(philo->table->sem_check);
	if (is_dying(philo))
	{
		// sem_post(philo->table->sem_check);
		exit(EXIT_FAILURE);
	}
	sem_post(philo->table->sem_check);
	if (print_start(philo, THINKING) < 0)
		exit(EXIT_FAILURE);
	return (0);
}
