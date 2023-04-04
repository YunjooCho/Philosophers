/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:59:33 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/05 05:57:11 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_table *table)
{
	int		idx;
	pid_t	pid;

	idx = 0;
	table->start_time = get_now();
	while (idx < table->philo_cnt)
	{
		parent_proc(&table->philos[idx], &pid);
		if (!pid)
			children_proc(&table->philos[idx]);
		idx++;
	}
	return (0);
}

void	parent_proc(t_philo *philo, int *pid)
{
	*pid = fork();
	philo->pid = *pid;
}

void	children_proc(t_philo *philo)
{
	int count = 0;
	
	while (1)
	{
		pickup_forks(philo);
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
		count++;
		if (count == 30)
			break;
	}
}