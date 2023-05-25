/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:59:33 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/25 19:06:37 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_table *table)
{
	int	idx;
	int	result;

	idx = 0;
	result = 0;
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
		usleep(philo->table->time_to_die / 2);
	while (1)
	{
		pickup_forks(philo);
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	kill_allprocesses(t_table *table)
{
	int		idx;
	pid_t	philo_pid;

	idx = 0;
	while (idx < table->philo_cnt)
	{
		philo_pid = table->philos[idx].pid;
		thread_kill(&table->philos[idx]);
		kill(philo_pid, SIGKILL);
		printf("Dead philo id : %d\n", table->philos[idx].philo_id);
		idx++;
	}
}

void	wait_processes(t_table *table)
{
	int	ret;
	int	count;
	int	status;

	count = 0;
	while (count < table->philo_cnt)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
			exit(EXIT_FAILURE);
		else
			count++;
		if (count)
			kill_allprocesses(table);
	}
	exit(0);
}
