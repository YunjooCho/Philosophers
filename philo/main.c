/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:27 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/29 17:31:39 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table table;

	if (ac <= 4 || ac >= 7)
		return (print_error("Incorrect number of parameters"));
	if (init_table(av, &table) == -1)
		return (print_error("Parsing Fail"));
	
	// printf("table addr : %p\n", &table);
	// print_philos(table.philo_cnt, table.philos);

	if (create_threads(&table) == -1)
		return (print_error("Create Thread Fail"));
}