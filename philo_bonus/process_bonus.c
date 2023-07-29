/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:59:33 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/29 21:43:45 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_table *table)
{
	int	idx;

	idx = 0;
	table->start_time = get_now();
	while (idx < table->philo_cnt)
	{
		table->philos[idx].lasteat_time = table->start_time;
		table->philos[idx].pid = fork();
		if (!table->philos[idx].pid)
			philo_task(&table->philos[idx]);
		idx++;
	}
	wait_processes(table);
	return (0);
}

void	philo_task(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->table->time_to_die / 2);
	while (1)
	{
		pickup_forks(philo);
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	wait_processes(t_table *table)
{
	int	ret;
	int	count;
	int	status;

	count = 0;
	while (1)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
			exit(EXIT_FAILURE);
		else
		{
			count++;
			//Debugging
			// printf("wait_processed count : %d\n", count);
		}
		if (count && table->must_eat_cnt == -1)
			kill_allprocesses(table);
	}
	exit(0);
}

void	kill_allprocesses(t_table *table)
{
	int		idx;
	pid_t	philo_pid;

	idx = 0;
	while (idx < table->philo_cnt)
	{
		philo_pid = table->philos[idx].pid;
		process_kill(&table->philos[idx]);
		kill(philo_pid, SIGKILL);
		idx++;
		// printf("Dead philo id : %d\n", table->philos[idx].philo_id);
	}
	sem_post(table->sem_check);
	sem_post(table->sem_print);
}
