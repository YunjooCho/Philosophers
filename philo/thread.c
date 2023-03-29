/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:44:45 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/29 17:33:41 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	idx;

	idx = 0;
	table->start_time = get_now();
	
	printf("init start_time : %ld\n", table->start_time);

	while (idx < table->philo_cnt)
	{
		if (pthread_create(&table->philos[idx].thread, NULL, philo_task, \
		(void *)&table->philos[idx]) == -1)
		{
			while (idx >= 0)
				pthread_detach(table->philos[idx--].thread);
			return (-1);
		}
		idx++;
		break ;
	}
	while(1)
	{
		
	}
	return (0);
}

void	*philo_task(void *argument)
{
	t_philo *philo;

	philo = NULL;
	philo = (void *)argument;
	while(1)
	{ 
		if (pickup_forks(philo) == -1)
		{
			//TODO - Debugging
			printf("%d Can't Pickup Forks\n", philo->philo_id);
			//TODO - Debugging
			continue ;
		}
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	pickup_forks(t_philo *philo)
{
	unsigned long	pickup_time;

	pickup_time = 0;
	if (philo->left_fork->used)
		return (-1);
	else
		philo->left_fork->used = USED;
	if (philo->right_fork->used)
		return (-1);
	else
		philo->right_fork->used = USED;
	pickup_time = get_printms(philo->table->start_time);
	printf("%ld %d has taken a fork\n", pickup_time, philo->philo_id);
	return (0);
}

void	eating(t_philo *philo)
{
	unsigned long	eatstart_time;
	unsigned long	eating_time;
	unsigned long	print_time;

	eating_time = 0;
	eatstart_time = get_now();
	print_time = get_printms(philo->table->start_time);
	printf("eatstart time : %ld\n", eatstart_time);
	printf("%ld %d is eating\n", print_time, philo->philo_id);
	while (1)
	{
		eating_time = get_printms(eatstart_time);
		if (eating_time == (unsigned long)philo->table->time_to_eat)
		{
			//TODO - Debugging
			unsigned long	eatend_time = 0;
			printf("%d aft starttime : %ld\n", philo->philo_id, philo->table->start_time);
			eatend_time = get_printms(philo->table->start_time);
			printf("%ld %d eating over\n", eatend_time, philo->philo_id);
			//TODO - Debugging

			break ;
		}
	}
}

void	putdown_forks(t_philo *philo)
{
	if (philo->left_fork->used)
		philo->left_fork->used = NOT_USED;
	if (philo->right_fork->used)
		philo->right_fork->used = NOT_USED;

	//TODO - Debugging
	unsigned long	putdown_time;
	putdown_time = get_printms(philo->table->start_time);
	printf("%ld %d putdown a fork\n", putdown_time, philo->philo_id);
	//TODO - Debugging
}

void	sleeping(t_philo *philo)
{
	unsigned long	sleepstart_time;
	unsigned long	sleeping_time;
	unsigned long	print_time;

	sleepstart_time = get_now();
	sleeping_time = 0;
	print_time = get_printms(philo->table->start_time);
	printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	while (1)
	{
		if (sleeping_time == (unsigned long)philo->table->time_to_sleep)
		{
			
			//TODO - Debugging
			unsigned long	sleepend_time = 0;
			printf("%d aft starttime : %ld\n", philo->philo_id, philo->table->start_time);
			sleepend_time = get_printms(philo->table->start_time);
			printf("%ld %d eating over\n", sleepend_time, philo->philo_id);
			//TODO - Debugging

			break ;
		}
	}
}

void	thinking(t_philo *philo)
{
	unsigned long	print_time;

	print_time = get_printms(philo->table->start_time);
	printf("%ld %d is thinking\n", print_time, philo->philo_id);
}