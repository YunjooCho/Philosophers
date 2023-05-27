/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:23:15 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/27 19:53:46 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_table *table)
{
	int	idx;

	idx = 0;
	while (idx < table->philo_cnt)
	{
		sem_post(table->sem_forks);
		idx++;
	}
	sem_post(table->sem_print);
	sem_post(table->sem_check);
	sem_close(table->sem_forks);
	sem_close(table->sem_print);
	sem_close(table->sem_check);
	sem_unlink(table->sem_forksname);
	sem_unlink(table->sem_printname);
	sem_unlink(table->sem_checkname);
	free(table->philos);
}
