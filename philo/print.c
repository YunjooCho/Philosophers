/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:57:39 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/31 18:25:05 by yunjcho          ###   ########.fr       */
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
		printf("forks[%d] used : %d\n", \
		idx + 1, forks[idx].used);
		idx++;
	}
}
