/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:09:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/23 17:21:00 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philothreads(int idx)
{
	int			result;
	pthread_t	thread;
	t_philo		*new;

	new = NULL;
	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
	{
		printf("Fork Malloc Fail\n");
		return (new);
	}
	init_philo(new, idx);
	result = pthread_create(&thread, NULL, tmp_print, &idx);
	printf("init philo idx : %d, result : %d\n", idx + 1, result);
	if (result < 0)
	{
		free(new);
		return (new);
	}
	new->thread = &thread;
	return (new);
}

void	*tmp_print(void *idx)
{
	int *ch = (int *)idx;
	printf("Hi! %d Thread\n", *ch);
	return (NULL);
}
