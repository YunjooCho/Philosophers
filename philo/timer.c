/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:06:40 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/27 17:47:12 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_now(void)
{
	struct timeval	now;
	long long		now_time;

	now_time = 0;
	gettimeofday(&now, NULL); // -1일 때 예외 처리?
	now_time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (now_time);
}

long long	get_diffMilliSec(long long start_time)
{
	long long	end_time;
	long long	diffTime;

	end_time = get_now();
	diffTime = end_time - start_time;
	return (diffTime);
}

// // void	ft_usleep(int time)
// // {
// // }


// int	is_dying(t_table *table)
// {
// 	int	diffTime;
// 	int	philo_idx;

// 	diffTime = 0;
// 	philo_idx = table->cur_idx;
// 	while (diffTime < table->time_to_die)
// 		diffTime = (int)print_diffMilliSec(table->philos[philo_idx]->lasteating_time);
// 	if (diffTime == table->time_to_die)
// 	{
// 		table->is_dying++;
// 		printf("%0.0f ms %ld died\n", print_diffMilliSec(table), philo_idx);
// 		return (1);
// 	}
// 	return (0);
// }

