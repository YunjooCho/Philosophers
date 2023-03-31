/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:27 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/31 18:14:35 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	_leaks_check(void)
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	int		flag;
	t_table	table;

	flag = 0;
	if (ac <= 4 || ac >= 7)
	{
		// system("leaks philo");
		return (print_error("Incorrect number of parameters"));
	}
	if (init_table(av, &table) == -1)
	{
		// system("leaks philo");
		return (print_error("Parsing Fail"));
	}
	print_table(&table);
	flag = create_threads(&table);
	if (flag == -1)
	{
		// system("leaks philo");
		return (print_error("Create Thread Fail"));
	}	
	else if (flag == -2)
	{
		// system("leaks philo");
		return (print_error("Philosopher died"));
	}
	print_philos(table.philo_cnt, table.philos);
	// system("leaks philo");
	// atexit(_leaks_check);
	return (0);
}
