/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:30:04 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/21 18:28:31 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(int idx, int result, t_table *table)
{
	table->must_eat_cnt = -1;
	table->is_dying = 0;
	if (idx == 1)
		table->philo_cnt = result;
	else if (idx == 2)
		table->time_to_die = result;
	else if (idx == 3)
		table->eating_time = result;
	else if (idx == 4)	
		table->sleeping_time = result;
	else if (idx == 5)
		table->must_eat_cnt = result;
}

int	init_forks(t_fork *fork)
{
	int		result;

	result = -1;
	fork = malloc(sizeof(t_fork *));
	if (!fork)
	{
		printf("Fork Malloc Fail\n");
		return (result);
	}
	result = pthread_mutex_init(&fork->fork_lock, NULL);
	if (result == -1)
	{
		printf("Mutex Init Error\n");
		return (result);
	}
	fork->used = 0;
	return (result);
}

int	init_philo(t_philo *philo, int idx)
{
	int			result;
	pthread_t	thread;	

	result = -1;
	philo = malloc(sizeof(t_philo *));
	if (!philo)
	{
		printf("Fork Malloc Fail\n");
		return (result);
	}
	philo->philo_id = idx + 1;
	philo->status = -1;
	philo->eat_cnt = 0;
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	philo->thread = NULL;
	result = pthread_create(&thread, NULL, tmp_print, &idx);
	if (result < 0)
		return (result);
	philo->thread = &thread;
	return (result);
}

void	*tmp_print(void *idx)
{
	int *i = (int *)idx;
	printf("Hi! Thread %d\n", *i);
	return (NULL);
}