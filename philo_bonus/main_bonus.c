/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:11:29 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/29 22:03:10 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// ★★★★★★먹고나서 바로 종료되어 출력되는 문장이 없으므로 비주얼라이저에서 3번만 찍히는 경우 존재★★★★★★
// void	_leaks(void)
// {
// 	system("leaks philo_bonus");
// }

int	main(int ac, char **av)
{
	t_table	table;

	// atexit(_leaks);
	if (ac <= 4 || ac >= 7)
		return (print_error("Incorrect number of parameters"));
	if (init_table(av, &table) == -1)
		return (print_error("Init table Fail"));
	create_process(&table);
	// print_table(&table);
	// print_philos(table.philo_cnt, table.philos);
	free_all(&table);
	return (0);
}
