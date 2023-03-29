/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:09:58 by yunjcho           #+#    #+#             */
/*   Updated: 2023/03/28 20:36:48 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philothreads(t_table *table)
{
	long	idx;
	t_philo	*philos;

	idx = 0;
	philos = table->philos;
	table->born_time = get_now();
	while (idx < table->philo_cnt)
	{
		if (pthread_create(&philos[idx].thread, NULL, \
		philo_task, (void *)&philos[idx]) < 0)
			return (print_error("Create Threads Fail"));
		idx++;
	}
	while (1)
	{
		//TODO - wait() 수정 필요 (노션)
	}
	return (0);
}

void	*philo_task(void *arg)//TODO - is_dying() 처리하기 (모니터 스레드? 함수?)
{
	t_philo	*philo;
	t_fork	*forks;

	philo = NULL;
	philo = (t_philo *)arg;
	forks = philo->table->forks;
	philo->lasteating_time = get_now();
	if (!(philo->philo_id % 2))
		usleep(3000);
	while (1)
	{
		if (philo->eat_cnt == philo->table->must_eat_cnt)
		{
			// printf("[philo_task] %d breakpoint-------------------------\n", philo->philo_id);
			// printf("philo's eat cnt : %d, repeat : %d\n", philo->eat_cnt, philo->table->must_eat_cnt);
			break ;
		}
		while (1) //글로벌 뮤텍스 잠금/해제 | 포크 뮤텍스 잠금/해제
		{
			if (!pickup_forks(philo, forks))
				break ;
			// printf("[philo_task] philo %d is waiting...\n", philo->philo_id);
		}
		eating(philo);
		putdown_forks(philo, forks); // 포크 뮤텍스 잠금/해제
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	pickup_forks(t_philo *philo, t_fork *forks)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (check_forks(philo, forks) == -1)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int	check_forks(t_philo *philo, t_fork *forks)
{
	long long	print_time;

	if (philo->philo_id % 2 != 0)
	{
		if (check_leftfork(philo, forks) == -1)
			return (-1);
		if (check_rightfork(philo, forks) == -1)
			return (-1);
	}
	else
	{
		if (check_rightfork(philo, forks) == -1)
			return (-1);
		if (check_leftfork(philo, forks) == -1)
			return (-1);
	}
	// philo->status = EATING;
	philo->eat_cnt++;
	print_time = get_printms(philo->table->born_time); //스레드 생성 ~ 포크 집은 시간
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld ms %d has taken a fork\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}

int	check_leftfork(t_philo *philo, t_fork *forks)
{
	int	result;

	result = 0;
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
	while (print_time <= philo->table->eating_time)
	{
		print_time = get_printms(philo->table->born_time); //포크를 집음 ~ 식사 종료 : (식사 시간)
		if (print_time == philo->table->eating_time)
			philo->lasteating_time = get_now();
	}
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld ms %d is eating\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	putdown_forks(t_philo *philo, t_fork *forks)
{	
	//TODO - 내려놓을 때도 홀수 / 짝수 순서 반대? (데드락)
	if (philo->philo_id % 2 != 0)
	{
		putdown_leftfork(philo, forks);
		putdown_rightfork(philo, forks);
	}
	else
	{
		putdown_rightfork(philo, forks);
		putdown_leftfork(philo, forks);
	}
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("[putdown_forks] Philo %d Status : %d\n", philo->philo_id, philo->status); //TODO - Debugging용 추후 삭제
	pthread_mutex_unlock(&philo->table->print_mutex);
}

int	putdown_leftfork(t_philo *philo, t_fork *forks)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&forks[philo->left_fork].fork_lock);
	if (forks[philo->left_fork].used == USED)
		forks[philo->left_fork].used = NOT_USED;
	else
		result = -1;
	pthread_mutex_unlock(&forks[philo->left_fork].fork_lock);
	return (result);
}

int	putdown_rightfork(t_philo *philo, t_fork *forks)
{
	int	result;

	result = 0;
	pthread_mutex_unlock(&forks[philo->right_fork].fork_lock);
	if (forks[philo->right_fork].used == USED)
		forks[philo->right_fork].used = NOT_USED;
	pthread_mutex_unlock(&forks[philo->right_fork].fork_lock);
	return (result);
}

void	sleeping(t_philo *philo)
{
	long long	print_time;

	print_time = 0;
	// philo->status = SLEEPING;
	while (print_time <= philo->table->sleeping_time)
	{
		print_time = get_printms(philo->lasteating_time); //식사 종료 ~ 잠 종료(깨어난 시간)
		if (print_time == philo->table->eating_time)
			philo->table->born_time = get_now();
	}
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld ms %d is sleeping\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	thinking(t_philo *philo)
{
	long long	print_time;

	print_time = 0;
	// philo->status = THINKING;
	print_time = get_printms(philo->table->born_time);
	philo->table->born_time = get_now();
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld ms %d is thinking\n", print_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

// int	is_dying(t_table *table)
// {
// 	int	diffTime;
// 	int	philo_idx;
// 	diffTime = 0;
// 	philo_idx = table->cur_idx;
// 	while (diffTime < table->time_to_die)
// 		diffTime = (int)print_diffMilliSec(table->philos[philo_idx]->lasteating_time);
// 	if (diffTime == table->time_to_die)
// 	{
// 		table->is_dying++;
// 		printf("%0.0f ms %ld died\n", print_diffMilliSec(table), philo_idx);
// 		return (1);
// 	}
// 	return (0);
// }