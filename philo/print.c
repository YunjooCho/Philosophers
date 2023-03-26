/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:57:39 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/26 21:34:00 by yunjcho          ###   ########.fr       */
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
	printf("table philo : %ld, time_to_die : %d, eat time : %d, sleep time : %d, eat cnt : %d, die : %d\n", \
	table->philo_cnt, table->time_to_die, table->eating_time, \
	table->sleeping_time, table->must_eat_cnt, table->is_dying);
}

void	print_philos(int cnt, t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < cnt)
	{
		printf("philos[%d] status : %d, eat_cnt : %d, left_fork : %ld, right_fork : %ld, last eat time : %lld, table : %p, thread : %p\n", \
		philos[idx].philo_id, philos[idx].status, philos[idx].eat_cnt, philos[idx].left_fork, philos[idx].right_fork, philos[idx].lasteating_time, \
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
