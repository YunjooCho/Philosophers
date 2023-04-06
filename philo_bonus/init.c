/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:22:55 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/06 14:16:46 by yunjcho          ###   ########.fr       */
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
	philo->fork_cnt = 0;
	philo->table = table;
	philo->lasteat_time = table->start_time;
	if (pthread_mutex_init(&philo->philo_mutex, NULL) < 0)
		return (-1);
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
	const char	*sem_name;

	sem_name = "sem_forks";
	translate_aton(av, table);
	if (!table->philo_cnt)
		return (-1);
	if (pthread_mutex_init(&table->check_mutex, NULL) < 0 || \
		pthread_mutex_init(&table->print_mutex, NULL) < 0 || \
		pthread_mutex_init(&table->table_mutex, NULL) < 0)
		return (-1);
	if (table->time_to_die < 0 || table->time_to_eat < 0 || \
		table->time_to_sleep < 0 || table->philo_cnt < 0)
		return (-1);
	sem_unlink(sem_name);
	table->sem_forks = sem_open(sem_name, O_CREAT | O_EXCL, 0777, table->philo_cnt);
	table->philos = malloc_philosarr(table);
	if (!table->sem_forks || !table->philos)
		return (-1);
	return (0);
}
