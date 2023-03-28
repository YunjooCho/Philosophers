/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:10:26 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/27 16:46:23 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forkmutexs(t_fork *fork)
{
	int	result;

	result = pthread_mutex_init(&fork->fork_lock, NULL);
	if (result == -1)
	{
		printf("Mutex Init Error\n");
		return (result);
	}
	fork->used = NOT_USED;
	return (result);
}
