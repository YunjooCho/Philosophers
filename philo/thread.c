/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:44:45 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/29 18:03:00 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	idx;

	idx = 0;
	table->start_time = get_now();
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
	philo->lasteat_time = philo->table->start_time;
	while(1)
	{ 
		if (pickup_forks(philo) == -1)
		{
			//TODO - Debugging
			// pthread_mutex_lock(&philo->table->print_mutex);
			// printf("%d Can't Pickup Forks\n", philo->philo_id);
			// pthread_mutex_unlock(&philo->table->print_mutex);
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

int	check_leftfork(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	if (!philo->left_fork->used)
	{
		philo->left_fork->used = USED;
		philo->left_fork->last_author = philo->philo_id;
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		if (check_rightfork(philo) == -1)
		{
			pthread_mutex_lock(&philo->left_fork->fork_mutex);
			philo->left_fork->used = NOT_USED;
			philo->left_fork->last_author = philo->philo_id;
			pthread_mutex_unlock(&philo->left_fork->fork_mutex);
			return (-1);
		}
	}
	else
		result = -1;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	return (result);
}

int	check_rightfork(t_philo *philo)
{
	int result;

	result = 0;
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	if (!philo->right_fork->used)
	{
		philo->right_fork->used = USED;
		philo->right_fork->last_author = philo->philo_id;
	}
	else
		result = -1;
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	return (result);
}

int	pickup_forks(t_philo *philo)
{
	unsigned long	pickup_time;

	pickup_time = 0;
	if (check_leftfork(philo) == -1)
		return (-1);
	pickup_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n", pickup_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
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
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is eating\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	while (1)
	{
		eating_time = get_printms(eatstart_time);
		if (eating_time == (unsigned long)philo->table->time_to_eat)
		{
			//TODO - Debugging
			unsigned long	eatend_time = 0;
			pthread_mutex_lock(&philo->table->print_mutex);
			eatend_time = get_printms(philo->table->start_time);
			printf("%ld %d eating over\n", eatend_time, philo->philo_id);
			pthread_mutex_unlock(&philo->table->print_mutex);
			//TODO - Debugging
			philo->lasteat_time = get_now();
			philo->eat_cnt++;
			break ;
		}
	}
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_mutex);
	if (philo->left_fork->used)
		philo->left_fork->used = NOT_USED;
	if (philo->right_fork->used)
		philo->right_fork->used = NOT_USED;
	pthread_mutex_unlock(&philo->table->check_mutex);

	//TODO - Debugging
	unsigned long	putdown_time;
	putdown_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d putdown a fork\n", putdown_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
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
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	while (1)
	{
		sleeping_time = get_printms(sleepstart_time);
		if (sleeping_time == (unsigned long)philo->table->time_to_sleep)
		{
			
			//TODO - Debugging
			unsigned long	sleepend_time = 0;
			pthread_mutex_lock(&philo->table->print_mutex);
			sleepend_time = get_printms(philo->table->start_time);
			printf("%ld %d sleeping over\n", sleepend_time, philo->philo_id);
			pthread_mutex_unlock(&philo->table->print_mutex);
			//TODO - Debugging
			break ;
		}
	}
}

void	thinking(t_philo *philo)
{
	unsigned long	print_time;

	print_time = get_printms(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is thinking\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}