/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:59:33 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/08 22:02:20 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_table *table)
{
	int		idx;
	int		result;

	idx = 0;
	result = 0;
	table->start_time = get_now();
	while (idx < table->philo_cnt)
	{
		table->philos[idx].lasteat_time = table->start_time;
		table->philos[idx].pid = fork();
		if (!table->philos[idx].pid)
			philo_task(&table->philos[idx]);
		printf("parent proc - child : %d\n", table->philos[idx].pid); //부모 프로세스에서 모니터링?
		idx++;
	}
	monitoring(table);
	wait_processes(table->philo_cnt);
	return (0);
}

void	philo_task(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(philo->table->time_to_die / 2);
	printf("<<<<<<<children proc id : %d>>>>>>\n", philo->philo_id);
	while (1)
	{
		pickup_forks(philo);
		eating(philo);
		putdown_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
}

int	monitoring(t_table *table)
{
	int	idx;
	int	result;
	int	alleat_cnt;

	idx = 0;
	result = 0;
	alleat_cnt = 0;
	printf("monitoring()\n");
	while (1)
	{
		printf("monitoring() while\n");
		if (is_dying(table, idx))
		{
			result = -2;
			break ;
		}
		if (is_musteat(table, idx, &alleat_cnt))
		{
			result = -1;
			break ;
		}
		idx = (idx + (table->philo_cnt - 1)) % table->philo_cnt;
		usleep(400);
	}
	kill(table->philos[idx].pid, SIGKILL); //TODO - 첫번째 인자 및 함수 위치 맞는 지 확인
	return (result);
}


int	is_dying(t_table *table, int idx)
{
	unsigned long	print_time;
	unsigned long	noteating_time;

	print_time = 0;
	noteating_time = 0;
	sem_wait(table->sem_check);
	noteating_time = get_printms(table->philos[idx].lasteat_time);
	sem_post(table->sem_check);
	if (noteating_time > (unsigned long)table->time_to_die)
	{
		sem_wait(table->sem_table);
		table->is_dying = idx + 1;
		print_time = get_printms(table->start_time);
		sem_post(table->sem_table);
		sem_wait(table->sem_print);
		printf("%ld %d is died\n", print_time, table->is_dying);
		sem_post(table->sem_print);
		return (1);
	}
	return (0);
}

int	is_musteat(t_table *table, int idx, int *alleat_cnt)
{
	if (is_end(&table->philos[idx]))
		return (-1);
	sem_wait(table->sem_check);
	if (is_end(&table->philos[idx]))
	{
		sem_post(table->sem_check);
		return (-1);
	}
	if (table->philos[idx].eat_cnt == table->must_eat_cnt \
		&& !(table->philos[idx].checked))
	{
		(*alleat_cnt)++;
		table->philos[idx].checked = USED;
		sem_post(table->sem_check);
		if (*alleat_cnt == table->philo_cnt)
		{
			if (is_end(&table->philos[idx]))
				return (-1);
			sem_wait(table->sem_table);
			table->is_dying = idx + 1;
			sem_post(table->sem_table);
			return (1);
		}
	}
	sem_post(table->sem_table);
	return (0);
}

void	wait_processes(int len)
{
	int	ret;
	int	count;
	int	status;

	count = 0;
	printf("wait_processes()\n");
	while (count < len)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
			exit(EXIT_FAILURE);
		count++;
		if (count)
			kill(0, SIGKILL);
	}
}