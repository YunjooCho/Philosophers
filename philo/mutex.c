/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:10:26 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/22 23:21:52 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*create_forkmutexs(void)
{
    int     result;
	t_fork	*new;

    result = 0;
    new = NULL;
	new = (t_fork *)malloc(sizeof(t_fork));
	if (!new)
	{
		printf("Fork Malloc Fail\n");
		return (new);
	}
	result = pthread_mutex_init(&new->fork_lock, NULL);
	if (result == -1)
	{
		printf("Mutex Init Error\n");
        free(new);
		return (new);
	}
	new->used = 0;
	return (new);
}

// void	ft_usleep(int time)
// {
// }