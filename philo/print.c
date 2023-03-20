/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:57:39 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/20 21:46:03 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	printf("table philo : %d, fork : %d, life time : %d, \
	eat time : %d, sleep time : %d, eat cnt : %d, die : %d\n", \
	table->philo_cnt, table->fork_cnt, table->life_time, table->eating_time, \
	table->sleeping_time, table->eating_cnt, table->dying_cnt);
}