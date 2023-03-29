/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:44:45 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/29 21:02:59 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	idx;

	idx = 0;
	table->start_time = get_now();
	printf("Init start time : %ld\n", table->start_time);
	while (idx < table->philo_cnt)
	{
		if (pthread_create(&table->philos[idx].thread, NULL, philo_task, \
		(void *)&table->philos[idx]) == -1)
		{
			while (idx >= 0)
				pthread_detach(table->philos[idx--].thread);
			return (-1);
		}
		idx++;
	}
	while(1)
	{
		// is_dying(table);
		//while(philo_cnt)
			//int cnt;
			//필로구조체 순회하면서 현재 시간 - 최근 먹은시간 > 안먹으면 죽는시간
			// if (현재 시간 - 최근 먹은시간 > 안먹으면 죽는시간 == true)
					//table.isdying = true;
			//if(현재 필로 eat_cnt == must_eat)
				//ent++	
		// if (cnt == 필로 인원수)
				//table.isdying = true;
	}
	/*while (필로수)
	{
		wait - 현재 확인 중인 스레드가 죽을 때까지 계속 대기
		pthread_join();
	}*/
	return (0);
}


// int	is_dying(t_table *table)
// {
// 	int				idx;
// 	t_philo 		*philos;
// 	unsigned long	noteating_time;

// 	idx = 0;
// 	noteating_time = 0;
// 	philos = table->philos;
// 	while(idx < table->philo_cnt)
// 	{
// 		pthread_mutex_lock(&philos[idx].philodying_mutex);
// 		noteating_time = get_printms(philos[idx].lasteat_time);
// 		pthread_mutex_unlock(&philos[idx].philodying_mutex);
// 		if (noteating_time > (unsigned long)table->time_to_die)
// 		{
// 			pthread_mutex_lock(&table->dying_mutex);
// 			table->is_dying = DIED;
// 			printf("%d Died\n", idx + 1);
// 			pthread_mutex_unlock(&table->dying_mutex);
// 			return (DIED);
// 		}
// 		usleep(400);
// 		idx++;
// 	}
// 	return (NOT_DIED);
// }