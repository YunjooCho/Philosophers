/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:27 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/31 18:32:49 by yunjcho          ###   ########.fr       */
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
		return (print_error("Init table Fail"));
	}
	print_table(&table);
	print_forks(table.philo_cnt, table.forks);
	print_philos(table.philo_cnt, table.philos);
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

//철학자가 1명 일 때는 바로 죽어도 됨? 아니면 수명 시간까지 버텨야 됨? - init.c
//시간 밀리는 것 수정
//join() 처리