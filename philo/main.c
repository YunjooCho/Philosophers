/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:07:27 by yunjcho           #+#    #+#             */
/*   Updated: 2023/04/03 17:49:53 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		flag;
	t_table	table;

	flag = 0;
	if (ac <= 4 || ac >= 7)
		return (print_error("Incorrect number of parameters"));
	if (init_table(av, &table) == -1)
		return (print_error("Init table Fail"));
	flag = create_threads(&table);
	if (flag == -1)
		return (print_error("Create Thread Fail"));
	else if (flag == -2)
		return (print_error("Philosopher died"));
	return (0);
}
//leaks 체크 시 스레드가 계속 출력됨
//./philo 3 50 200 100