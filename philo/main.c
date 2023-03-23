/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:25 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/23 18:16:32 by yunjcho          ###   ########.fr       */
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
		// system("leaks philo");
		return (print_error("Incorrect number of parameters"));
	}
	//1. 인자값 파싱 & table 구조체에 인자 정보 저장 
	if (parsing_arg(av, &table) == -1)
	{
		// system("leaks philo");
		return (print_error("Parsing Fail"));
	}
	print_table(&table);
	//2. philos & forks 구조체 배열 malloc
	philos = malloc_philosarr(table.philo_cnt);
	forks = malloc_forksarr(table.philo_cnt);
	if (!philos || !forks)
	{
		// system("leaks philo");
		return (print_error("Array Malloc Fail"));
	}
	//3. 구조체 배열 초기화
	//   - 철학자 수만큼 스레드 생성 및 데이터 초기화
	//   - 포크 수만큼 뮤텍스 생성 및 포크 상태 미사용으로 초기화
	if (init_arrays(&table, philos, forks) == -1)
	{
		// system("leaks philo");
		return (print_error("Init Arrays Fail"));
	}
	print_philos(table.philo_cnt, philos);//TODO - 데이터 정상입력 확인용, 추후 삭제
	print_forks(table.philo_cnt, forks);
	
	//4. create eating function
	//5. create monitoring thread
	
	// system("leaks philo");
	return (0);
}
