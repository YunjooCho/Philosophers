/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    thread_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:58:51 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/28 21:01:38 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*philo_task(void *arg)//TODO - is_dying() 처리하기 (모니터 스레드? 함수?)
{
	t_philo	*philo;
	t_fork	*forks;

	philo = NULL;
	philo = (t_philo *)arg;
	forks = philo->table->forks;
	while(1)
	{
		eating(philo);
		sleeping();
		thinking();
	}
	return (NULL);
}

void	eating()



