/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:06:40 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/05 03:21:32 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long	get_now(void)
{
	struct timeval	now;
	unsigned long	now_time;

	now_time = 0;
	gettimeofday(&now, NULL);
	now_time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (now_time);
}

unsigned long	get_printms(unsigned long start_time)
{
	unsigned long	end_time;
	unsigned long	diff_time;

	end_time = get_now();
	diff_time = end_time - start_time;
	return (diff_time);
}
