/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    thread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:44:45 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/28 21:53:52 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	idx;

	idx = 0;
	while (idx < table->philo_cnt)
	{
		if (pthread_create(table->philos[idx].thread, NULL, routine, \
		(void *)&table->philos[idx]) == -1)
		{
			while (idx >= 0)
				pthread_detach(table->philos[idx--].thread);
			return (-1);
		}
		idx++;
	}
	return (0);
}

void	*routine(void *argument)
{
	t_philo *philo;

	philo = NULL;
	philo = (void *)argument;
	while(1)
	{
		//eating();
		//sleeping();
		//thinkin();
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	pickup_forks();
	print();
	dininig();
	putdown_forks();
}

void	sleeping(t_philo *philo)
{
	print();
}

void	thinking(t_philo *philo)
{
	print();
}