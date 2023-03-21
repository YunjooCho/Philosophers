/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:09:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/21 18:34:43 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_table *table, t_philo **philos, t_fork **forks)
{
	int	idx;

	idx = 0;
	while(idx < table->philo_cnt)
	{
		if (init_philo(philos[idx], idx) == -1)
			return ;
		if (init_forks(forks[idx]) == -1)
			return ;
		idx++;
	}
}