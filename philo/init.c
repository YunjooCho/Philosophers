/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:22:55 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/29 17:51:25 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, t_table *table, int idx)
{
	int	right_idx;

	right_idx = (idx + (table->philo_cnt - 1)) % table->philo_cnt;
	philo->philo_id = idx + 1;
	philo->eat_cnt = 0;
	philo->left_fork = &table->forks[idx];
	philo->right_fork = &table->forks[right_idx];
	philo->table = table;
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
		init_philo(&philos_arr[idx], table, idx);
		idx++;
	}
	return (philos_arr);
}

int	create_forkmutexs(t_fork *fork)
{
	int	result;

	result = pthread_mutex_init(&fork->fork_mutex, NULL);
	if (result == -1)
	{
		printf("Mutex Init Error\n");
		return (result);
	}
	fork->used = NOT_USED;
	fork->last_author = -1;
	return (result);
}

t_fork	*malloc_forksarr(int forks_cnt)
{
	int		idx;
	t_fork	*forks_arr;

	idx = 0;
	forks_arr = NULL;
	forks_arr = (t_fork *)malloc((sizeof(t_fork) * forks_cnt));
	if (!forks_arr)
		return (forks_arr);
	while (idx < forks_cnt)
	{
		if (create_forkmutexs(&forks_arr[idx]) == -1)
		{
			free(forks_arr);
			return (NULL);
		}
		idx++;
	}
	return (forks_arr);
}

int	init_table(char **av, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < sizeof(t_table))
		*((char *)table + i++) = 0;
	table->philo_cnt = ph_atoi(av[1]);
	table->time_to_die = ph_atoi(av[2]);
	table->time_to_eat = ph_atoi(av[3]);
	table->time_to_sleep = ph_atoi(av[4]);
	if (av[5])
		table->must_eat_cnt = ph_atoi(av[5]);
	if (table->time_to_die < 0 || table->time_to_eat < 0 || \
		table->time_to_sleep < 0 || table->must_eat_cnt < 0 || \
		table->philo_cnt < 0)
		return (-1);
	table->forks = malloc_forksarr(table->philo_cnt);
	table->philos = malloc_philosarr(table);
	return (0);
}