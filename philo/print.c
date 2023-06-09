/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:57:39 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/13 15:18:55 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str)
{
	if (!str)
		printf("Error\n");
	else if (*str)
		printf("Error : %s\n", str);
	return (-1);
}

int	print_start(t_philo *philo, int flag)
{
	unsigned long	print_time;

	print_time = 0;
	if (is_end(philo))
		return (-1);
	pthread_mutex_lock(&philo->table->print_mutex);
	print_time = get_printms(philo->table->start_time);
	if (is_end(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (-1);
	}
	if (flag == TAKEFORKS)
		printf("%ld %d has taken a fork\n", \
			print_time, philo->philo_id);
	else if (flag == EATING)
		printf("%ld %d is eating\n", print_time, philo->philo_id);
	else if (flag == SLEEPING)
		printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	else
		printf("%ld %d is thinking\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	if (is_end(philo))
		return (-1);
	return (0);
}

void	print_table(t_table *table)
{
	printf("table philo_cnt : %d, time_to_die : %ld, time_to_eat : %ld, \
		time_sleep_time : %ld, must_eat_cnt : %ld, start_time : %ld, \
		is_dying : %d\n", \
		table->philo_cnt, table->time_to_die, table->time_to_eat, \
		table->time_to_sleep, table->must_eat_cnt, table->start_time, \
		table->is_dying);
}

void	print_philos(int cnt, t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < cnt)
	{
		printf("philos[%d] eat_cnt : %d, left_fork : %p, right_fork : %p, \
		last eat time : %ld, table : %p, thread : %p\n", \
		philos[idx].philo_id, philos[idx].eat_cnt, philos[idx].left_fork, \
		philos[idx].right_fork, philos[idx].lasteat_time, \
		philos[idx].table, philos[idx].thread);
		idx++;
	}
}

void	print_forks(int cnt, t_fork *forks)
{
	int	idx;

	idx = 0;
	while (idx < cnt)
	{
		printf("forks[%d] %p used : %d\n", \
		idx + 1, &forks[idx], forks[idx].used);
		idx++;
	}
}
