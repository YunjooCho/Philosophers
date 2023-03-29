/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:30:04 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/28 21:06:11 by yunjcho          ###   ########.fr       */
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
		if (pthread_mutex_init(&table->mutex, NULL) < -1 || pthread_mutex_init(&table->print_mutex, NULL) < -1 )
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
	int	right_idx;

	right_idx = (idx + (table->philo_cnt - 1)) % table->philo_cnt;
	philo->philo_id = idx + 1;
	philo->status = THINKING;
	philo->eat_cnt = 0;
	philo->left_fork = &table->forks[idx];
	philo->right_fork = &table->forks[right_idx];
	philo->lasteating_time = 0;
	philo->table = table;
	philo->table->born_time = 0;
	philo->thread = NULL;
}
