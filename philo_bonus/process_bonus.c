/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:59:33 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/06 21:18:30 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_table *table)
{
	int		idx;

	idx = 0;
	table->start_time = get_now();
	while (idx < table->philo_cnt)
	{
		
		table->philos[idx].lasteat_time = table->start_time;
		table->philos[idx].pid = fork();
		if (!table->philos[idx].pid)
			philo_task(&table->philos[idx]);
		printf("parent proc\n");
		idx++;
	}
	return (0);
}

void	philo_task(t_philo *philo)
{
	printf("<<<<<<<children proc id : %d, pid : %d>>>>>>\n", philo->philo_id, philo->pid);
	int count = 0;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		printf("-------------------check_task---------------------\n");
		pickup_forks(philo);
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
		count++;
		if (count == 4)
			return ;
	}
}