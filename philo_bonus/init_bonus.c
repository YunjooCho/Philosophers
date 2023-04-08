/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:22:55 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/08 21:07:43 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_philo *philo, t_table *table, int idx)
{
	int	right_idx;

	right_idx = (idx + (table->philo_cnt - 1)) % table->philo_cnt;
	philo->pid = 0;
	philo->philo_id = idx + 1;
	philo->eat_cnt = 0;
	philo->leftfork_cnt = 0;
	if (idx == right_idx)
		philo->rightfork_cnt = -1;
	else
		philo->rightfork_cnt = 0;
	philo->table = table;
	philo->lasteat_time = table->start_time;
	philo->checked = NOT_USED;
	return (0);
}

t_philo	*malloc_philosarr(t_table *table)
{
	long	idx;
	t_philo	*philos_arr;

	idx = 0;
	philos_arr = NULL;
	philos_arr = (t_philo *)malloc((sizeof(t_philo) * table->philo_cnt));
	if (!philos_arr)
		return (philos_arr);
	while (idx < table->philo_cnt)
	{
		if (init_philo(&philos_arr[idx], table, idx) == -1)
			free(philos_arr);
		idx++;
	}
	return (philos_arr);
}

int	init_table(char **av, t_table *table)
{
	translate_aton(av, table);
	if (!table->philo_cnt || table->time_to_die < 0 || \
		table->time_to_eat < 0 || table->time_to_sleep < 0 \
		|| table->philo_cnt < 0)
		return (-1);
	table->useable_forkcnt = table->philo_cnt;
	table->sem_forksname = "sem_forks";
	table->sem_printname = "sem_print";
	table->sem_checkname = "sem_check";
	table->sem_tablename = "sem_table";
	sem_unlink(table->sem_forksname);
	sem_unlink(table->sem_printname);
	sem_unlink(table->sem_checkname);
	sem_unlink(table->sem_tablename);
	table->sem_forks = sem_open(table->sem_forksname, O_CREAT | O_EXCL, \
		0777, table->philo_cnt);
	table->sem_print = sem_open(table->sem_printname, O_CREAT | O_EXCL, \
		0777, 1);
	table->sem_check = sem_open(table->sem_checkname, O_CREAT | O_EXCL, \
		0777, 1);
	table->sem_table = sem_open(table->sem_tablename, O_CREAT | O_EXCL, \
		0777, 1);
	table->philos = malloc_philosarr(table);
	if (!table->sem_forks || !table->sem_print || !table->sem_check \
		|| !table->philos)
		return (-1);
	return (0);
}
