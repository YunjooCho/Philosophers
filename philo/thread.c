/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:09:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/27 21:17:36 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philothreads(t_table *table)
{
	long	idx;
	t_philo *philos;

	idx = 0;
	philos = table->philos;
	while (idx < table->philo_cnt)
	{
		// table->cur_idx = idx;
		if (pthread_create(&philos[idx].thread, NULL, philo_task, (void *)&philos[idx]) < 0)
			return (print_error("Create Threads Fail"));
		idx++;
	}

	//wait();
	while (1)
	{
		int cnt;

		cnt = 0;
		if (!pthread_join(table->philos[idx].thread, NULL))
		{
			cnt++;
			if (cnt == table->philo_cnt)
				break ;
		}
	}
	return (0);
}

void	*philo_task(void *arg)
{
	//TODO - is_dying() 처리하기 (모니터 스레드? 함수?)

	t_philo	*philo;
	t_fork	*forks;

	philo = NULL;
	philo = (t_philo *)arg;
	forks = philo->table->forks;
	philo->lasteating_time = get_now();
	// printf("[philo_task] %d Last Eat time First Init : %lld\n", philo->philo_id, philo->lasteating_time);
	usleep(3000);
	if (!pickup_forks(philo, forks)) //글로벌 뮤텍스 잠금/해제 | 포크 뮤텍스 잠금/해제
	{
		eating(philo);
		putdown_forks(philo, forks); // 포크 뮤텍스 잠금/해제
	}
	// pickup_forks(philo, forks);  //글로벌 뮤텍스 잠금/해제 | 포크 뮤텍스 잠금/해제
	// eating(philo);
	// putdown_forks(philo, forks); // 포크 뮤텍스 잠금/해제
	sleeping(philo);
	thinking(philo, forks);         //pickup_forks를 호출해야 함(수정 필요)
	// usleep(7000);
	pthread_exit(0);
	return (NULL);
}

int	pickup_forks(t_philo *philo, t_fork *forks)
{
	if (!(philo->philo_id % 2))
	{
		printf("Philosopher : %d usleep(3000)\n", philo->philo_id);
		usleep(3000);
	}
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->status == THINKING)
	{
		if (check_forks(philo, forks) == -1)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return(-1);
		}
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int	check_forks(t_philo *philo, t_fork *forks)
{
	long long	print_time;

	if (philo->philo_id % 2 != 0)
	{
		// printf("[check_forks odd] philo_id : %d, left : %ld, right : %ld\n", philo->philo_id, philo->left_fork, philo->right_fork);
		// printf("[check_forks odd left] check result : %d\n", check_leftfork(philo, forks));
		// printf("[check_forks odd right] check result : %d\n", check_rightfork(philo, forks));
		if (check_leftfork(philo, forks) == -1)
			return (-1);
		if (check_rightfork(philo, forks) == -1)
			return (-1);
	}
	else
	{
		usleep(3000);
		// printf("[check_forks odd] philo_id : %d, left : %ld, right : %ld\n", philo->philo_id, philo->left_fork, philo->right_fork);
		// printf("[check_forks even right] check result : %d\n", check_rightfork(philo, forks));
		// printf("[check_forks even left] check result : %d\n", check_leftfork(philo, forks));
		if (check_rightfork(philo, forks) == -1)
			return (-1);
		if (check_leftfork(philo, forks) == -1)
			return (-1);
	}
	philo->status = EATING;
	philo->eat_cnt++;
	philo->lastworking_time = get_now();
	print_time = get_diffMilliSec(philo->lasteating_time); //태어나고나서 포크를 집은 시간
	printf("%lld ms %d has taken a fork\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int	check_leftfork(t_philo *philo, t_fork *forks)
{
	int	result;

	result = 0;
	// printf("[check_leftfork] philo_id : %d, left : %ld\n", philo->philo_id, philo->left_fork);
	pthread_mutex_lock(&forks[philo->left_fork].fork_lock);
	if (!forks[philo->left_fork].used)
		forks[philo->left_fork].used = USED;
	else
		result = -1;
	pthread_mutex_unlock(&forks[philo->left_fork].fork_lock);
	return (result);
}

int	check_rightfork(t_philo *philo, t_fork *forks)
{
	int result;

	result = 0;
	// printf("[check_leftfork] philo_id : %d, left : %ld\n", philo->philo_id, philo->right_fork);
	pthread_mutex_lock(&forks[philo->right_fork].fork_lock);
	if (!forks[philo->right_fork].used)
		forks[philo->right_fork].used = USED;
	else
		result = -1;
	pthread_mutex_unlock(&forks[philo->right_fork].fork_lock);
	return (result);
}

void eating(t_philo *philo)
{
	long long	print_time;
	t_fork		*forks;

	print_time = 0;
	forks = philo->table->forks;
	if (philo->status == EATING)
	{
		while (print_time <= philo->table->eating_time)
		{
			print_time = get_diffMilliSec(philo->lastworking_time);
			if (print_time == philo->table->eating_time)
				philo->lasteating_time = get_now();
		}
		// printf("[eating] Philosopher %d pickup forks time : %lld\n", philo->philo_id, philo->lastworking_time);
		// printf("[eating] Philosopher %d last eating time : %lld\n", philo->philo_id, philo->lasteating_time);
		printf("%lld ms %d is eating\n", print_time, philo->philo_id);
	}
}

void	putdown_forks(t_philo *philo, t_fork *forks)
{
	if (philo->status == EATING)
	{	
		//TODO - 내려놓을 때도 홀수 / 짝수 순서 반대?
		//왼쪽 포크
		pthread_mutex_lock(&forks[philo->left_fork].fork_lock);
		if (forks[philo->left_fork].used == USED)
			forks[philo->left_fork].used = NOT_USED;
		
		printf("-------------------------[putdown_forks Left Complete] Debugging Start----------------------------\n");
		printf("Philo %d putdown ", philo->philo_id);
		char *left_str = "";
		if (forks[philo->left_fork].used == USED)
			left_str = "USED";
		else if (forks[philo->left_fork].used == NOT_USED)
			left_str = "NOT_USED";
		printf("left fork : %ld - %s\n", philo->left_fork, left_str);
		printf("-------------------------[putdown_forks Left Complete] Debugging End----------------------------\n");
		
		pthread_mutex_unlock(&forks[philo->left_fork].fork_lock);
		


		
		//오른쪽 포크
		pthread_mutex_unlock(&forks[philo->right_fork].fork_lock);
		if (forks[philo->right_fork].used == USED)
			forks[philo->right_fork].used = NOT_USED;
		
		printf("-------------------------[putdown_forks Right Complete] Debugging Start----------------------------\n");
		printf("Philo %d putdown ", philo->philo_id);
		char *right_str = "";
		if (forks[philo->right_fork].used == USED)
			right_str = "USED";
		else if (forks[philo->right_fork].used == NOT_USED)
			right_str = "NOT_USED";
		printf("right fork : %ld - %s\n", philo->right_fork, right_str);
		printf("-------------------------[putdown_forks Right Complete] Debugging End----------------------------\n");
		
		print_forks(philo->table->philo_cnt, forks);
		pthread_mutex_unlock(&forks[philo->right_fork].fork_lock);
		

		printf("[putdown_forks] Philo %d Status : %d\n", philo->philo_id, philo->status);
		//TODO - 다른 스레드 께우기 추가
		
	}
}

void	sleeping(t_philo *philo)
{
	long long	print_time;

	print_time = 0;
	if (philo->status == EATING)
	{
		philo->status = SLEEPING;
		while (print_time <= philo->table->sleeping_time)
		{
			print_time = get_diffMilliSec(philo->lasteating_time);
			if (print_time == philo->table->eating_time)
				philo->lastworking_time = get_now();
		}
		// printf("[eating] Philosopher %d pickup forks time : %lld\n", philo->philo_id, philo->lastworking_time);
		// printf("[eating] Philosopher %d last eating time : %lld\n", philo->philo_id, philo->lasteating_time);
		printf("%lld ms %d is sleeping\n", print_time, philo->philo_id);
	}
}

void	thinking(t_philo *philo, t_fork *forks)
{
	long long	print_time;

	print_time = 0;
	if (philo->status == SLEEPING)
	{
		philo->status = THINKING;
		while (1)
		{
			print_time = get_diffMilliSec(philo->lasteating_time);
			if (print_time == philo->table->eating_time)
				philo->lastworking_time = get_now();
			printf("%lld ms %d is sleeping\n", print_time, philo->philo_id);
			if (!pickup_forks(philo, forks)) //글로벌 뮤텍스 잠금/해제 | 포크 뮤텍스 잠금/해제 (밖에 선언된 함수 호출할 수 없는 지?)
			{
				break ;
				// philo->lastworking_time = get_now();
				// eating(philo);
				// putdown_forks(philo, forks); // 포크 뮤텍스 잠금/해제
			}
		}
	}
}