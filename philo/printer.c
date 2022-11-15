/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:49:30 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/15 16:15:58 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_printer *printer, int self, int stat)
{
	const struct timeval	start_time = printer->start_time;

	self += 1;
	pthread_mutex_lock(printer->print_mut);
	if (stat == FORK)
		printf("%lld %d %s\n", get_elapsed(start_time), self, FORK_MSG);
	else if (stat == EAT)
		printf("%lld %d %s\n", get_elapsed(start_time), self, EAT_MSG);
	else if (stat == SLEEP)
		printf("%lld %d %s\n", get_elapsed(start_time), self, SLEEP_MSG);
	else if (stat == THINK)
		printf("%lld %d %s\n", get_elapsed(start_time), self, THINK_MSG);
	else
		printf("%lld %d %s\n", get_elapsed(start_time), self, DEAD_MSG);
	pthread_mutex_unlock(printer->print_mut);
}

static void	put_forks_down(t_collector *clct)
{
		put_fork_down(clct->table, clct->self, NULL, 0);
		put_fork_down(clct->table, (clct->self + 1) % \
					clct->input->philo_num, NULL, 0);
}

int	printer(t_collector *clct, int stat)
{
	if (check_table_flag(clct->table, PAUSE))
	{
		put_forks_down(clct);
		return (1);
	}
	if (stat == EAT)
	{
		if (get_elapsed(*clct->printer->last_eat[clct->self]) > \
				clct->input->time_die)
		{
			put_forks_down(clct);
			print_msg(clct->printer, clct->self, DEAD);
			return (1);
		}
		gettimeofday(clct->printer->last_eat[clct->self], NULL);
		print_msg(clct->printer, clct->self, stat);
		if (clct->input->must_eat != -1)
			if (++clct->printer->eat_cnt[clct->self] == clct->input->must_eat)
				add_ate_all(clct->printer);
	}
	else
		print_msg(clct->printer, clct->self, stat);
	return (0);
}

int	printer_fork(t_collector *clct, int stat, int pos)
{
	if (check_table_flag(clct->table, PAUSE))
	{
		put_fork_down(clct->table, clct->self, NULL, 0);
		if (pos == R_FORK)
			put_fork_down(clct->table, (clct->self + 1) % \
					clct->input->philo_num, NULL, 0);
		return (1);
	}
	print_msg(clct->printer, clct->self, stat);
	return (0);
}
