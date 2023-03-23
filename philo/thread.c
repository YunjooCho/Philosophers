/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:09:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/23 22:33:39 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philothreads(int thread_cnt, int idx)
{
	int			result;
	long		idx_back;
	pthread_t	thread[thread_cnt];
	t_philo		*new;

	idx_back = idx;
	new = NULL;
	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
	{
		printf("Fork Malloc Fail\n");
		return (new);
	}
	init_philo(new, idx_back);
	result = pthread_create(&thread[idx_back], NULL, task, (void *)idx_back);
	if (result < 0)
	{
		free(new);
		return (new);
	}
	new->thread = &thread[idx_back];
	return (new);
}

void	*task(void *idx_back)
{
	struct timeval	cur_time;
	long			i;
	
	i = (long)idx_back;
	if (gettimeofday(&cur_time, NULL) == -1)
	{
		printf("gettimeofday() Fail\n");
		return ;
	}
	printf("[%d] %ld has taken a fork\n", cur_time.tv_usec, i+1);
	printf("[%d] %ld is eating\n", cur_time.tv_usec, i+1);
	printf("[%d] %ld is sleeping\n", cur_time.tv_usec, i+1);
	printf("[%d] %ld is thinking\n", cur_time.tv_usec, i+1);
	printf("[%d] %ld died\n", cur_time.tv_usec, i+1);
	// pthread_exit(0);
	return (NULL);
}

void	get_milSec(struct timeval cur_time)
{
	
}