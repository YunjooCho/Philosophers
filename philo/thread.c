/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:44:45 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/13 15:21:50 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	idx;
	int	result;

	idx = 0;
	result = 0;
	table->start_time = get_now();
	while (idx < table->philo_cnt)
	{
		table->philos[idx].lasteat_time = table->start_time;
		if (pthread_create(&table->philos[idx].thread, NULL, philo_task, \
		(void *)&table->philos[idx]) == -1)
		{
			while (idx >= 0)
				pthread_detach(table->philos[idx--].thread);
			return (-1);
		}
		idx++;
	}
	result = monitoring(table);
	threads_join(table);
	return (result);
}

int	monitoring(t_table *table)
{
	int	idx;
	int	result;
	int	alleat_cnt;

	idx = 0;
	result = 0;
	alleat_cnt = 0;
	while (1)
	{
		if (is_dying(table, idx))
		{
			result = -2;
			break ;
		}
		if (table->must_eat_cnt > 0)
		{
			result = is_musteat(table, idx, &alleat_cnt);
			if (result == -2 || result == 1)
				break ;
		}
		idx = (idx + (table->philo_cnt - 1)) % table->philo_cnt;
		usleep(50);
	}
	return (result);
}

int	is_dying(t_table *table, int idx)
{
	unsigned long	print_time;
	unsigned long	noteating_time;

	print_time = 0;
	noteating_time = 0;
	pthread_mutex_lock(&table->philos[idx].philo_mutex);
	noteating_time = get_printms(table->philos[idx].lasteat_time);
	pthread_mutex_unlock(&table->philos[idx].philo_mutex);
	if (noteating_time > (unsigned long)table->time_to_die)
	{
		print_time = get_printms(table->start_time);
		pthread_mutex_lock(&table->print_mutex);
		printf("%ld %d is died\n", print_time, idx + 1);
		pthread_mutex_unlock(&table->print_mutex);
		pthread_mutex_lock(&table->table_mutex);
		table->is_dying = idx + 1;
		pthread_mutex_unlock(&table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->philos[idx].philo_mutex);
	return (0);
}

int	is_musteat(t_table *table, int idx, int *alleat_cnt)
{
	pthread_mutex_lock(&table->philos[idx].philo_mutex);
	if (is_end(&table->philos[idx]))
	{
		pthread_mutex_unlock(&table->philos[idx].philo_mutex);
		return (-2);
	}
	if (table->philos[idx].eat_cnt == table->must_eat_cnt \
		&& !(table->philos[idx].checked))
	{
		(*alleat_cnt)++;
		table->philos[idx].checked = USED;
		pthread_mutex_unlock(&table->philos[idx].philo_mutex);
		if (*alleat_cnt == table->philo_cnt)
		{
			if (is_end(&table->philos[idx]))
				return (-2);
			pthread_mutex_lock(&table->table_mutex);
			table->is_dying = idx + 1;
			pthread_mutex_unlock(&table->table_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&table->philos[idx].philo_mutex);
	return (0);
}

int	threads_join(t_table *table)
{
	int	idx;

	idx = 0;
	while (idx < table->philo_cnt)
	{
		pthread_join(table->philos[idx].thread, NULL);
		idx++;
	}
	return (0);
}
