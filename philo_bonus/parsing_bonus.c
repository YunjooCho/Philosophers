/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:25:19 by yunjcho           #+#    #+#             */
/*   Updated: 2023/05/27 19:39:19 by yunjcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	translate_aton(char **av, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < sizeof(t_table))
		*((char *)table + i++) = 0;
	table->philo_cnt = ph_atoi(av[1]);
	table->time_to_die = ph_atoi(av[2]);
	table->time_to_eat = ph_atoi(av[3]);
	table->time_to_sleep = ph_atoi(av[4]);
	if (!av[5])
		table->must_eat_cnt = -1;
	else
		table->must_eat_cnt = ph_atoi(av[5]);
}
