/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:55:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/14 21:44:09 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

//프로세스?
typedef struct s_table
{
	int	philo_cnt;     //철학자 수(number_of_philosophers)
	int	fork_cnt;      //포크의 개수(number_of_philosophers)
	int	life_time;     //철학자 수명(time_to_die) - ms
	int	eating_time;   //밥먹는데 걸리는 시간(time_to_eat) - ms
	int	sleeping_time; //잠자는데 걸리는 시간(time_to_sleep) - ms
	int	eating_cnt;    //철학자가 최소한 밥을 먹어야 하는 횟수(number_of_times_each_philosopher_must_eat)
	int	dying_cnt;     //죽은 철학자 수, 기본 0으로 1이 되면 종료
}	t_table;

//스레드
typedef struct s_philo
{
	int	philo_id;     //철학자 식별 코드
	int	seat_num;     //좌석 번호
	int	*left_fork;   //철학자가 가지고 있는 포크
	int	*right_fork;  //철학자가 가지고 있는 포크
}	t_philo;

void	parsing_arg(char **av, t_table *table);
void	init_table(int idx, int result, t_table *table);
int		is_digit(int c);
int		is_plus_minus(char *str, int i);
int		is_all_zero(char *str, int i); //TODO - 필요없으면 삭제
int		ph_atoi(char *str);
void	print_exit(int flag);
void	print_table(t_table *table);

#endif