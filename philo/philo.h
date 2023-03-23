/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:55:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/23 22:22:35 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2

typedef struct s_table
{
	int	philo_cnt;     //철학자 수(number_of_philosophers)
	int	time_to_die;   //철학자 수명(time_to_die) - ms
	int	eating_time;   //밥먹는데 걸리는 시간(time_to_eat) - ms
	int	sleeping_time; //잠자는데 걸리는 시간(time_to_sleep) - ms
	int	must_eat_cnt;  //(옵션) 철학자가 최소한 밥을 먹어야 하는 횟수(number_of_times_each_philosopher_must_eat)
	int	is_dying;      //철학자 사망 여부, 기본 0으로 1이 되면 종료
}	t_table;

//스레드 (모니터링 스레드는 별도 생성 또는 메인이 하기)
typedef struct s_philo
{
	int				philo_id;     //철학자 식별 번호
	int				status;       //현재 상태 0 - 먹기, 1 - 자기, 3 - 생각하기, 4 - 죽음
	int				eat_cnt;	  //철학자가 식사한 수
	struct t_fork	*left_fork;   //철학자가 가지고 있는 포크
	struct t_fork	*right_fork;  //철학자가 가지고 있는 포크
	pthread_t		*thread;      //스레드 주소값
}	t_philo;

//공용 데이터 - 각 포크마다 뮤텍스
typedef struct s_fork
{
	pthread_mutex_t fork_lock;//포크 뮤텍스
	int				used;	  //해당 포크의 사용여부
}	t_fork;


int		parsing_arg(char **av, t_table *table);
int		is_digit(int c);
int		is_plus_minus(char *str, int idx);
int		check_operators(char *str, int idx);
int		ph_atoi(char *str);

void	init_table(int idx, int result, t_table *table);
int		init_arrays(t_table *table, t_philo **philos, t_fork **forks);
void	init_philo(t_philo *new, int idx);

t_philo	**malloc_philosarr(int philos_cnt);
t_fork	**malloc_forksarr(int forks_cnt);

t_philo	*create_philothreads(int thread_cnt, int idx);
void 	*task(void *idx_addr);

t_fork	*create_forkmutexs(void);

int		print_error(char *str);
void	print_table(t_table *table);
void	print_philos(int cnt, t_philo **philos);
void	print_forks(int cnt, t_fork **forks);

#endif