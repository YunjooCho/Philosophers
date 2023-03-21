/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:25:19 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/21 15:25:05 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing_arg(char **av, t_table *table)
{
	int	idx;
	int	result;

	idx = 1;
	while (av[idx])
	{
		result = ph_atoi(av[idx]);
		if (result == -1)
		{
			printf("Error\n");
			return ;
		}
		init_table(idx, result, table);
		idx++;
	}
	print_table(table);
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
	return (1);
}

int	ph_atoi(char *str)
{
	long long	i;
	long long	n;
	long long	result;

	i = 0;
	n = 1;
	result = 0;
	
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
	{
		if (!is_plus_minus(str, i))
			return (-1);
		else
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
