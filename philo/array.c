/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:46:47 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/25 22:22:27 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**malloc_philosarr(int philos_cnt)
{
	int		idx;
	t_philo	**philos_arr;

	idx = 0;
	philos_arr = NULL;
	philos_arr = (t_philo **)malloc((sizeof(t_philo *) * philos_cnt));
	if (!philos_arr)
		return (philos_arr);
	while (idx < philos_cnt)
	{
		philos_arr[idx] = init_philo(idx);
		if (!philos_arr[idx])
			return (philos_arr);
		idx++;
	}
	return (philos_arr);
}

t_fork	**malloc_forksarr(int forks_cnt)
{
	int		idx;
	t_fork	**forks_arr;

	idx = 0;
	forks_arr = NULL;
	forks_arr = (t_fork **)malloc((sizeof(t_fork *) * forks_cnt));
	if (!forks_arr)
		return (forks_arr);
	while (idx < forks_cnt)
	{
		forks_arr[idx] = create_forkmutexs();
		if (!forks_arr[idx])
			return (forks_arr);
		idx++;
	}
	return (forks_arr);
}
