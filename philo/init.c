/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:25:19 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/15 20:40:12 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing_arg(char **av, t_table *table)
{
	int	idx;
	int	result;

	idx = 0;
	//0. 인자 검사 funtion 추가
	//1. 구조체 초기화
	while (av[idx])
	{
		result = ph_atoi(av[idx]);
		init_table(idx, result, table);
		idx++;
	}
	print_table(table);
	//2. 철학자 수 만큼 thread 생성
	// create_philo();
	//3. 포크 배열로 식별 번호 지정 및 사용 유무 표시?
}

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_plus_minus(char *str, int i)
{
	int	idx;

	idx = i;
	if (!is_digit(str[idx + 1]))
		return (0);
	if (str[idx] == '-')
		return (-1);
	return (1);
}

int	is_all_zero(char *str, int i)//TODO - 필요없으면 삭제
{
	int	idx;
	int	res;

	idx = i;
	res = 1;
	if (str[idx] != '0' || str[idx + 1] != '0')
		return (res);
	while (str[++idx])
	{
		if (str[idx] >= '1' && str[idx] <= '9')
			return (res);
	}
	res = 0;
	return (res);
}

int	ph_atoi(char *str)
{
	long long	i;
	long long	n;
	long long	result;

	i = 0;
	n = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (!is_plus_minus(str, i))
			return (-1);
		n = n * is_plus_minus(str, i);
		i++;
	}
	while (str[i])
	{
		if (!is_digit(str[i]))
		{
			printf("Error\n");
			return (-1);
		}
		result = result * 10 + (str[i] - '0') * n;
		if (result < INT_MIN || result > INT_MAX)
		{
			printf("Error\n");
			return (-1);
		}
		i++;
	}
	return ((int)result);
}

void	init_table(int idx, int result, t_table *table)
{
	table->eating_cnt = -1;
	table->dying_cnt = 0;
	if (idx == 1)
	{
		table->philo_cnt = result;
		table->fork_cnt = result;
	}
	else if (idx == 2)
		table->life_time = result;
	else if (idx == 3)
		table->eating_time = result;
	else if (idx == 4)	
		table->sleeping_time = result;
	else if (idx == 5)
		table->eating_cnt = result;
}
