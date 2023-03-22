/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:25 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/23 01:07:26 by yunjcho          ###   ########seoul.kr  */
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
	
	//2. create array(Malloc Array Space) : philos & forks
	philos = malloc_philosarr(table.philo_cnt);
	forks = malloc_forksarr(table.philo_cnt);
	if (!philos || !forks)
	{
		printf("Array Malloc Fail\n");
		return (1);
	}

	//3. thread
	if (init_arrays(&table, philos, forks) == -1)
	{
		printf("Init Arrays Fail\n");
		return (1);
	}
	print_philos(table.philo_cnt, philos);//TODO - 데이터 정상입력 확인용, 추후 삭제
	
	//4. create eating function
	//5. create monitoring thread
	
	return (0);
}

//2023.03.22
//1. thread.c
//	 - tmp_print()의 결과값 상이한 것 원인 찾아 처리 : 1, 2, 3, ... 이 아닌 1,1,3,4, 0으로 출력
//   - 모든 철학자의 thread 주소값이 동일한 것 처리
//2. Norm / Leaks