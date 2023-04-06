/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:29 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/06 21:12:20 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_table table;

	if (ac <= 4 || ac >= 7)
		return (print_error("Incorrect number of parameters"));
	if (init_table(av, &table) == -1)
		return (print_error("Init table Fail"));
	create_process(&table);
	print_table(&table);
	print_philos(table.philo_cnt, table.philos);
	return (0);
}