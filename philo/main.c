/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:25 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/20 22:05:13 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	
	//1. parsing
	if (ac <= 4 || ac >= 7)
	{
		printf("Incorrect number of parameters");
		return (0);
	}
	//2. init
	printf("hello\n");
	parsing_arg(av, &table);
	//3. create thread
	//4. make / set mutex
	return (0);
}