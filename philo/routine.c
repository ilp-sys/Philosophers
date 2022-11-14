/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:03:38 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/14 18:42:07 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_eat(t_collector clct, int time_eat)
{
	char		flag;
	const int	lpos = clct.self;
	const int	rpos = (clct.self + 1) % clct.input->philo_num;

	flag = 0;
	while (!(flag & L_FORK))
		(pick_fork_up(clct.table, lpos, &flag, L_FORK), usleep(10));
	if (printer(&clct, FORK))
		return (1);
	while (!(flag & R_FORK))
		(pick_fork_up(clct.table, rpos, &flag, R_FORK), usleep(10));
	if (printer(&clct, FORK))
		return (1);
	if (printer(&clct, EAT))
		return (1);
	if (timer_routine(clct, time_eat))
		return (1);
	while (flag & L_FORK)
		(put_fork_down(clct.table, lpos, &flag, L_FORK), usleep(10));
	while (flag & R_FORK)
		(put_fork_down(clct.table, rpos, &flag, R_FORK), usleep(10));
	return (0);
}

static int	philo_sleep(t_collector clct, int time_sleep)
{
	if (printer(&clct, SLEEP))
		return (1);
	if (timer_routine(clct, time_sleep))
		return (1);
	return (0);
}

static int	philo_think(t_collector clct, int time_think)
{
	if (printer(&clct, THINK))
		return (1);
	if (timer_routine(clct, time_think))
		return (1);
	return (0);
}

static void	pre_routine(t_collector clct, t_input *input, int *time_think)
{
	*time_think = (input->time_die - input->time_eat - input->time_sleep) / 2;
	if (*time_think <= 0)
		*time_think = 5;
	while (check_table_flag(clct.table, PAUSE))
		;
	if (clct.self % 2)
		timer_routine(clct, *time_think);
	if (input->philo_num % 2 == 0)
		*time_think = 0;
}

void	*routine(void *arg)
{
	int			time_think;
	t_collector	clct;
	t_input		*input;

	clct = *(t_collector *)arg;
	input = clct.input;
	pre_routine(clct, input, &time_think);
	while (1)
	{
		if (philo_eat(clct, input->time_eat))
			break ;
		if (input->must_eat != -1 && \
				check_ate_all(clct.printer, input->philo_num))
			break ;
		if (philo_sleep(clct, input->time_sleep))
			break ;
		if (philo_think(clct, time_think))
			break ;
	}
	set_table_flag(clct.table, PAUSE);
	return (NULL);
}
