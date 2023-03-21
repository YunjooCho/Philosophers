/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:57:39 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/21 18:27:59 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	printf("table philo : %d, time_to_die : %d, eat time : %d, sleep time : %d, eat cnt : %d, die : %d\n", \
	table->philo_cnt, table->time_to_die, table->eating_time, \
	table->sleeping_time, table->must_eat_cnt, table->is_dying);
}

void	print_philos(int cnt, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		printf("philos[%d] status : %d, left_fork : %p, right_fork : %p\n", \
		philos[i]->philo_id, philos[i]->status, philos[i]->left_fork, philos[i]->right_fork);
		i++;
	}
}