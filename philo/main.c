/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:25 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/25 23:16:53 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	// t_philo	**philos;
	// t_fork	**forks;

	// philos = NULL;
	// forks = NULL;
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
	//2. philos & forks 구조체 배열 malloc & init
	//   - 철학자 수만큼 t_philo 객체 생성 및 데이터 초기화
	//   - 포크 수만큼 t_fork 객체 생성 및 뮤텍스 & 포크 상태 미사용으로 초기화
	table.philos = malloc_philosarr(table.philo_cnt);
	table.forks = malloc_forksarr(table.philo_cnt);
	if (!table.philos || !table.forks)
	{
		// system("leaks philo");
		return (print_error("Array Malloc Fail"));
	}
	//3. 구조체 배열 초기화
	//   - 철학자 수만큼 스레드 생성 및 philos의 thread 변수에 스레드 주소 저장
	if (create_philothreads(&table, table.philos, table.forks) == -1)
	{
		// system("leaks philo");
		return (print_error("Create Threads Fail"));
	}
	print_philos(table.philo_cnt, table.philos);//TODO - 데이터 정상입력 확인용, 추후 삭제
	print_forks(table.philo_cnt, table.forks);  //TODO - 데이터 정상입력 확인용, 추후 삭제
	
	//4. create philo_task functions
	
	// system("leaks philo");
	return (0);
}
