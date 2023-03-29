/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:25 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/28 21:04:06 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac <= 4 || ac >= 7)
		return (print_error("Incorrect number of parameters"));
	if (parsing_arg(av, &table) == -1)
		return (print_error("Parsing Fail"));
	table.forks = malloc_forksarr(table.philo_cnt);
	table.philos = malloc_philosarr(&table);
	if (!table.philos || !table.forks)
		return (print_error("Array Malloc Fail"));
	table.philos->table = &table;
	//TODO - 데이터 정상입력 확인용, 추후 삭제
	// print_table(&table);
	// print_philos(table.philo_cnt, table.philos);
	// print_forks(table.philo_cnt, table.forks);
	if (create_philothreads(&table) == -1)
		return (-1);
	return (0);
}
