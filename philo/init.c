/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:30:04 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/23 16:52:20 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(int idx, int result, t_table *table)
{
	table->must_eat_cnt = -1;
	table->is_dying = 0;
	if (idx == 1)
		table->philo_cnt = result;
	else if (idx == 2)
		table->time_to_die = result;
	else if (idx == 3)
		table->eating_time = result;
	else if (idx == 4)
		table->sleeping_time = result;
	else if (idx == 5)
		table->must_eat_cnt = result;
}

int	init_arrays(t_table *table, t_philo **philos, t_fork **forks)
{
	int	idx;

	idx = 0;
	while (idx < table->philo_cnt)
	{
		philos[idx] = create_philothreads(idx);
		forks[idx] = create_forkmutexs();
		if (!philos[idx] || !forks[idx])
			return (-1);
		idx++;
	}
	return (0);
}

void	init_philo(t_philo *new, int idx)
{
	new->philo_id = idx + 1;
	new->status = -1;
	new->eat_cnt = 0;
	new->left_fork = NULL;
	new->right_fork = NULL;
	new->thread = NULL;
}
