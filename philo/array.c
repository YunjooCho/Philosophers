/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:46:47 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/23 16:52:00 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**malloc_philosarr(int philos_cnt)
{
	t_philo	**philos_arr;

	philos_arr = NULL;
	philos_arr = (t_philo **)malloc((sizeof(t_philo *) * philos_cnt));
	if (!philos_arr)
		return (philos_arr);
	return (philos_arr);
}

t_fork	**malloc_forksarr(int forks_cnt)
{
	t_fork	**forks_arr;

	forks_arr = NULL;
	forks_arr = (t_fork **)malloc((sizeof(t_fork *) * forks_cnt));
	if (!forks_arr)
		return (forks_arr);
	return (forks_arr);
}
