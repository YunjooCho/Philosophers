/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:09:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/26 22:00:42 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philothreads(t_table *table)
{
	long	idx;
	t_philo *philos;

	idx = 0;
	philos = table->philos;
	while (idx < table->philo_cnt)
	{
		// table->cur_idx = idx;
		if (pthread_create(&philos[idx].thread, NULL, philo_task, (void *)&philos[idx]) < 0)
			return (print_error("Create Threads Fail"));
		idx++;
	}
	print_philos(table->philo_cnt, table->philos);//TODO - 데이터 정상입력 확인용, 추후 삭제
	print_forks(table->philo_cnt, table->forks);  //TODO - 데이터 정상입력 확인용, 추후 삭제
	// idx = 0;
	// while (idx < table->philo_cnt)
	// {
	// 	int res = pthread_join(table->philos[idx]->thread, NULL);
	// 	printf("join result : %d\n", res);
	// 	idx++;
	// }
	return (0);
}

void	*philo_task(void *arg)
{
	t_philo	*philo;

	philo = NULL;
	philo = (t_philo *)arg;
	philo->lasteating_time = get_now();
	if (!pickup_forks(philo))
		eating(philo);
	// putdown_forks();
	// sleeping();
	// tinkking();
	pthread_exit(0);
	return (NULL);
}

int	pickup_forks(t_philo *philo)
{
	int	result;

	result = pthread_mutex_lock(&philo->table->mutex);
	if (result < 0)
	{
		printf("Mutex Lock Error : %d\n", result);
		return (-1);
	}
	if (philo->status == THINKING)
		check_forks(philo);
	else if (philo->status == SLEEPING)
		printf("Philosopher %d is sleeping\n", philo->philo_id);
	else if (philo->status == EATING)
	{
		printf("Philosopher %d is eating\n", philo->philo_id);
	}
	else if (philo->status == DYING)
		printf("Philosopher %d died\n", philo->philo_id);
	result = pthread_mutex_unlock(&philo->table->mutex);
	if (result < 0)
	{
		printf("Mutex Unlock Error : %d\n", result);
		return (-1);
	}
	return (0);
}

int	check_forks(t_philo *philo)
{
	long long	cur_time;
	t_fork		*forks;

	forks = philo->table->forks;
	if (!pthread_mutex_lock(&forks[philo->left_fork].fork_lock) \
	&& !pthread_mutex_lock(&forks[philo->right_fork].fork_lock))
	{
		philo->status = EATING;
		philo->eat_cnt++;
		cur_time = get_diffMilliSec(philo->lasteating_time);
		printf("%lld ms %d has taken a fork\n", cur_time, philo->philo_id);
	}
	else
	{
		printf("Philosopher %d can't Eating : %d\n", philo->philo_id, philo->status);
		pthread_mutex_unlock(&forks[philo->left_fork].fork_lock);
		pthread_mutex_unlock(&forks[philo->right_fork].fork_lock);
		return (-1);
	}
	return (0);
}

void eating(t_philo *philo)
{
	while (get_diffMilliSec(philo->eat_cnt) <= philo->table->eating_time)
	{
		if (get_diffMilliSec(philo->eat_cnt) == philo->table->eating_time)
			philo->lasteating_time = get_diffMilliSec(philo->eat_cnt);
	}
	// printf("%0.0f ms %ld is eating\n", diffTime, table->cur_idx);
}
