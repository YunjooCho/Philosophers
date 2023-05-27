/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:57:39 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/27 19:46:43 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(char *str)
{
	if (!str)
		printf("Error\n");
	else if (*str)
		printf("Error : %s\n", str);
	exit(1);
}

int	print_start(t_philo *philo, int flag)
{
	unsigned long	print_time;

	print_time = 0;
	sem_wait(philo->table->sem_check);
	if (is_dying(philo))
	{
		return (-1);
	}
	sem_post(philo->table->sem_check);
	print_time = get_printms(philo->table->start_time);
	sem_wait(philo->table->sem_print);
	if (flag == TAKEFORKS)
		printf("%ld %d has taken a fork\n", \
			print_time, philo->philo_id);
	else if (flag == EATING)
		printf("%ld %d is eating\n", print_time, philo->philo_id);
	else if (flag == SLEEPING)
		printf("%ld %d is sleeping\n", print_time, philo->philo_id);
	else
		printf("%ld %d is thinking\n", print_time, philo->philo_id);
	sem_post(philo->table->sem_print);
	return (0);
}

void	print_table(t_table *table)
{
	printf("table philo_cnt : %d, time_to_die : %ld, time_to_eat : %ld, \
		time_sleep_time : %ld, must_eat_cnt : %ld, start_time : %ld\n", \
		table->philo_cnt, table->time_to_die, table->time_to_eat, \
		table->time_to_sleep, table->must_eat_cnt, table->start_time);
	printf("sem_forks : %p, sem_print : %p, sem_check : %p\n", table->sem_forks, \
		table->sem_print, table->sem_check);
}

void	print_philos(int cnt, t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < cnt)
	{
		printf("philos[%d] pid: %d, eat_cnt : %d, leftfork_cnt : %d, \
		rightfork_cnt : %d, last eat time : %ld, table : %p\n", \
		philos[idx].philo_id, philos[idx].pid, philos[idx].eat_cnt, \
		philos[idx].leftfork_cnt, philos[idx].rightfork_cnt, \
		philos[idx].lasteat_time, philos[idx].table);
		idx++;
	}
}
