/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:46:47 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/28 21:40:06 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
