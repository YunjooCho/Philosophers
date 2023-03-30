/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:44:45 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/31 01:26:34 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int				idx;
	int				eat_cnt;
	unsigned long	print_time;
	unsigned long	noteating_time;

	idx = 0;
	eat_cnt = 0;
	print_time = 0;
	noteating_time = 0;
	table->start_time = get_now();
	// printf("Init start time : %ld\n", table->start_time);
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
	idx = 0;
	while (idx < table->philo_cnt)
	{
		pthread_mutex_lock(&table->philos[idx].philo_mutex);
		noteating_time = get_printms(table->philos[idx].lasteat_time);
		pthread_mutex_unlock(&table->philos[idx].philo_mutex);
		if (noteating_time > (unsigned long)table->time_to_die)
		{
			pthread_mutex_lock(&table->table_mutex);
			table->is_dying = idx + 1;
			pthread_mutex_unlock(&table->table_mutex);
			pthread_mutex_lock(&table->print_mutex);
			print_time = get_printms(table->start_time);
			printf("%ld %d is died\n", print_time, table->is_dying);
			pthread_mutex_unlock(&table->print_mutex);
			return (-2);
		}
		// (void) eat_cnt;
		pthread_mutex_lock(&table->philos[idx].philo_mutex);
		if (table->philos[idx].eat_cnt == table->must_eat_cnt && !(table->philos[idx].checked))
		{
			eat_cnt++;
			table->philos[idx].checked = 1;
			if (eat_cnt == table->philo_cnt)
			{
				pthread_mutex_lock(&table->table_mutex);
				table->is_dying = idx + 1;
				pthread_mutex_unlock(&table->table_mutex);
				pthread_mutex_lock(&table->print_mutex);
				printf("Every one must eat over\n");
				pthread_mutex_unlock(&table->print_mutex);
				return (0);
			}
		}
		pthread_mutex_unlock(&table->philos[idx].philo_mutex);
		idx = (idx + (table->philo_cnt - 1)) % table->philo_cnt;
		usleep(400);
	}
	// while(1)
	// {
		//while(philo_cnt)
			//int cnt;
			//필로구조체 순회하면서 현재 시간 - 최근 먹은시간 > 안먹으면 죽는시간
			// if (현재 시간 - 최근 먹은시간 > 안먹으면 죽는시간 == true)
					//table.isdying = true;
			//if(현재 필로 eat_cnt == must_eat)
				//ent++	
		// if (cnt == 필로 인원수)
				//table.isdying = true;
	// }
	/*while (필로수)
	{
		wait - 현재 확인 중인 스레드가 죽을 때까지 계속 대기
		pthread_join();
	}*/
	return (0);
}
