/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:30:04 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/25 23:18:36 by yunjcho          ###   ########seoul.kr  */
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
	table->philos = NULL;
	table->forks = NULL;
	table->cur_idx = -1;
}

t_philo	*init_philo(int idx)
{
	t_philo *new;

	new = NULL;
	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
	{
		printf("Philo Malloc Fail\n");
		return (new);
	}
	new->philo_id = idx + 1;
	new->status = NOTHING;
	new->eat_cnt = 0;
	new->left_fork = NULL;
	new->right_fork = NULL;
	new->thread = NULL;
	return (new);
}
