/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:25:19 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/26 16:01:46 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing_arg(char **av, t_table *table)
{
	int	idx;
	int	result;

	idx = 1;
	while (av[idx])
	{
		result = ph_atoi(av[idx]);
		if (result < 0 || init_table(idx, result, table) < 0)
			return (result);
		idx++;
	}
	return (0);
}

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_plus_minus(char *str, int idx)
{
	if (!is_digit(str[idx + 1]))
		return (0);
	return (1);
}

int	check_operators(char *str, int idx)
{
	if (str[idx] == '-')
		return (-1);
	else if (str[idx] == '+' && !is_plus_minus(str, idx))
		return (-1);
	return (0);
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
		if (!check_operators(str, i))
			i++;
		else
			return (-1);
	}
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (-1);
		result = result * 10 + (str[i] - '0') * n;
		if (result < INT_MIN || result > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)result);
}
