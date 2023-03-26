/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:30:04 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/26 21:37:27 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(int idx, int result, t_table *table)
{
	if (idx == 1)
	{
		table->must_eat_cnt = -1;
		table->is_dying = 0;
		table->philos = NULL;
		table->forks = NULL;
		// table->cur_idx = -1;
		if (pthread_mutex_init(&table->mutex, NULL) < -1)
			return (print_error("Mutex Init Error"));
		table->philo_cnt = result;
	}
	else if (idx == 2)
		table->time_to_die = result;
	else if (idx == 3)
		table->eating_time = result;
	else if (idx == 4)
		table->sleeping_time = result;
	else if (idx == 5)
		table->must_eat_cnt = result;
	return (0);
}

void	init_philo(t_philo *philo, t_table *table, int idx)
{
	philo->philo_id = idx + 1;
	philo->status = THINKING;
	philo->eat_cnt = 0;
	philo->left_fork = idx;
	philo->right_fork = (idx + (table->philo_cnt - 1)) % table->philo_cnt;
	philo->table = table;
	philo->thread = NULL;
}
