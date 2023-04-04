/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:59:33 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/05 00:11:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	parent_proc(t_table *table, t_philo *philos_arr, int idx, pid_t *pid)
{
	if (init_philo(&philos_arr[idx], table, idx, pid) == -1)
		free(philos_arr);
}

void	children_proc(void)
{
	printf("child\n");
}