/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:03:38 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 17:07:50 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_fork_up(t_table *table, int pos, char *flag, int flag_op)
{
	pthread_mutex_lock(table->fork_mut[pos]);
	if (table->fork[pos] == AVAIL)
	{
		table->fork[pos] = TAKEN;
		*flag |= flag_op;
	}
	pthread_mutex_unlock(table->fork_mut[pos]);
}

static void	put_fork_down(t_table *table, int pos, char *flag, int flag_op)
{
	pthread_mutex_lock(table->fork_mut[pos]);
	if (table->fork[pos] == TAKEN)
	{
		table->fork[pos] = AVAIL;
		*flag ^= flag_op;
	}
	pthread_mutex_unlock(table->fork_mut[pos]);
}

static int	philo_eat(t_collector clct, int time_eat)
{
	char		flag;
	const int	lpos = clct.self;
	const int	rpos = (clct.self + 1) % clct.input->philo_num;

	flag = 0;
	while (!(flag & L_FORK))
		pick_fork_up(clct.table, lpos, &flag, L_FORK);
	if (printer(&clct, FORK))
		return (1);
	while (!(flag & R_FORK))
		pick_fork_up(clct.table, rpos, &flag, R_FORK);
	if (printer(&clct, FORK))
		return (1);
	if (printer(&clct, EAT))
		return (1);
	timer(time_eat);
	while (flag & L_FORK)
		put_fork_down(clct.table, lpos, &flag, L_FORK);
	while (flag & R_FORK)
		put_fork_down(clct.table, rpos, &flag, R_FORK);
	return (0);
}

static int	philo_sleep(t_collector clct, int time_sleep)
{
	if (printer(&clct, SLEEP))
		return (1);
	timer(time_sleep);
	return (0);
}

static int	philo_think(t_collector clct, int time_think)
{
	if (printer(&clct, THINK))
		return (1);
	timer(time_think);
	return (0);
}

void		*routine(void *arg)
{
	int			time_think;
	t_collector	clct;
	t_input		*input;

	clct = *(t_collector *)arg;
	input = clct.input;
	time_think = (input->time_die - input->time_eat - input->time_sleep) / 2;
	if (time_think < 0)
		time_think = 5;
	while (check_table_flag(clct.table, PAUSE))
		;
	if (clct.self % 2)
		timer(time_think);
//	if (input->philo_num % 2 == 0)
//		time_think = 0;
	while (1)
	{
		if (philo_eat(clct, input->time_eat))
			break ;
		if (input->must_eat != -1 && check_ate_all(clct.printer, input->philo_num))
			break ;
		if (philo_sleep(clct, input->time_sleep))
			break ;
		if (philo_think(clct, time_think))
			break ;
	}
	set_table_flag(clct.table, PAUSE);
	return (NULL);
}
