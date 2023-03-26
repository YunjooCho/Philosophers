/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:06:40 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/26 21:41:41 by yunjcho          ###   ########.fr       */
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

// // void	ft_usleep(int time)
// // {
// // }

// double print_diffMilliSec(t_table *table)
// {
// 	struct timeval start_time;
// 	struct timeval end_time;
// 	double	diffTime;

// 	diffTime = ((end_time.tv_sec - start_time.tv_sec) * 1000)
// 	+ (((end_time.tv_usec - start_time.tv_sec) / 1000))
// 	return (diffTime);
// }

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

