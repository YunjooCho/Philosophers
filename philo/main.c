/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:27 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/03 17:07:21 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		flag;
	t_table	table;

	flag = 0;
	if (ac <= 4 || ac >= 7)
	{
		system("leaks philo");
		return (print_error("Incorrect number of parameters"));
	}
	if (init_table(av, &table) == -1)
	{
		system("leaks philo");
		return (print_error("Init table Fail"));
	}
	flag = create_threads(&table);
	if (flag == -1)
	{
		system("leaks philo");
		return (print_error("Create Thread Fail"));
	}	
	else if (flag == -2)
	{
		system("leaks philo");
		return (print_error("Philosopher died"));
	}
	print_philos(table.philo_cnt, table.philos);
	return (0);
}
//leaks 체크 시 스레드가 계속 출력됨
//./philo 3 50 200 100