/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:46:47 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/21 18:26:55 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**create_philosarr(int philo_cnt)
{
	t_philo	**philo_arr;

	philo_arr = malloc((sizeof(t_philo **) * philo_cnt));
	if (!philo_arr)
		return (NULL);
	return (philo_arr);
}

t_fork	**create_forksarr(int philo_cnt)
{
	t_fork	**forks_arr;

	forks_arr = malloc((sizeof(t_fork **) * philo_cnt));
	if (!forks_arr)
		return (NULL);
	return (forks_arr);
}