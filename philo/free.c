/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:23:15 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/13 12:58:58 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table)
{
	int	idx;

	idx = 0;
	while (idx < table->philo_cnt)
	{
		pthread_mutex_destroy(&table->forks[idx].fork_mutex);
		idx++;
	}
	pthread_mutex_destroy(&table->check_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->philos);
	free(table->forks);
}
