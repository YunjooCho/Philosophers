/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:25 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/21 18:16:21 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	**philos;
	t_fork	**forks;

	philos = NULL;
	forks = NULL;
	if (ac <= 4 || ac >= 7)
	{
		printf("Incorrect number of parameters");
		return (1);
	}
	//1. parsing & init_table
	parsing_arg(av, &table);
	//2. create array : philos & forks
	philos = create_philosarr(table.philo_cnt);
	forks = create_forksarr(table.philo_cnt);
	if (!philos || !forks)
	{
		printf("Array Malloc Fail\n");
		return (1);
	}
	//3. thread
	create_threads(&table, philos, forks);
	print_philos(table.philo_cnt, philos);
	//3. create monitoring thread
	return (0);
}