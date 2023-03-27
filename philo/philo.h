/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:55:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/27 21:30:46 by yunjcho          ###   ########.fr       */
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
# define DYING -1

# define USED 1
# define NOT_USED 0

typedef struct s_table
{
	long			philo_cnt;     //철학자 수(number_of_philosophers)
	int				time_to_die;   //철학자 수명(time_to_die) - ms
	int				eating_time;   //밥먹는데 걸리는 시간(time_to_eat) - ms
	int				sleeping_time; //잠자는데 걸리는 시간(time_to_sleep) - ms
	int				must_eat_cnt;  //(옵션) 철학자가 최소한 밥을 먹어야 하는 횟수(number_of_times_each_philosopher_must_eat)
	int				is_dying;      //철학자 사망 여부, 기본 0으로 1이 되면 종료
	struct s_philo	*philos;       //철학자 구조체 배열
	struct s_fork	*forks;        //포크 구조체 배열
	struct timeval	cur_time;      //현재 작업을 수행하려는 시간
	pthread_mutex_t	mutex;         //pickup_fork() 수행 시 하나의 철학자만 수행하기 위한 뮤텍스
}	t_table;

//스레드 (모니터링 스레드는 별도 생성 또는 메인이 하기)
typedef struct s_philo
{
	int				philo_id;         //철학자 식별 번호
	int				status;           //현재 상태 0 - 먹기, 1 - 자기, 3 - 생각하기, 4 - 죽음
	int				eat_cnt;	      //철학자가 식사한 수
	long			left_fork;        //철학자가 가지고 있는 포크
	long			right_fork;       //철학자가 가지고 있는 포크
	long long		lasteating_time;  //철학자가 마지막으로 식사한 시간
	long long		lastworking_time; //철학자가 마지막으로 포크를 집은 시간, 잔 시간
	struct s_table	*table;           //테이블 정보
	pthread_t		thread;           //스레드 주소값
}	t_philo;

//공용 데이터 - 각 포크마다 뮤텍스
typedef struct s_fork
{
	pthread_mutex_t fork_lock;  //포크 뮤텍스
	int				used;       //해당 포크의 사용여부
}	t_fork;


int			parsing_arg(char **av, t_table *table);
int			is_digit(int c);
int			is_plus_minus(char *str, int idx);
int			check_operators(char *str, int idx);
int			ph_atoi(char *str);

int			init_table(int idx, int result, t_table *table);
int			init_arrays(t_table *table, t_philo *philos);
void		init_philo(t_philo *philo, t_table *table, int idx);

t_philo		*malloc_philosarr(t_table *table);
t_fork		*malloc_forksarr(int forks_cnt);

int			create_forkmutexs(t_fork *fork);

int			create_philothreads(t_table *table);
void		*philo_task(void *arg);
int			pickup_forks(t_philo *philo, t_fork *forks);
int			check_forks(t_philo *philo, t_fork *forks);
int			check_leftfork(t_philo *philo, t_fork *forks);
int			check_rightfork(t_philo *philo, t_fork *forks);
void 		eating(t_philo *philo);
void		putdown_forks(t_philo *philo, t_fork *forks);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo, t_fork *forks);

long long	get_now(void);
long long	get_diffMilliSec(long long start_time);
// int		is_dying(t_table *table); //TODO

int			print_error(char *str);
void		print_table(t_table *table);
void		print_philos(int cnt, t_philo *philos);
void		print_forks(int cnt, t_fork *forks);


#endif