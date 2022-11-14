/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:38:45 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/14 16:43:41 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timer(int elapse)
{
	struct timeval	start;

	if (elapse > 0)
	{
		gettimeofday(&start, NULL);
		while (1)
		{
			if ((int)get_elapsed(start) >= elapse)
				return ;
			usleep(elapse);
		}
	}
}

int	timer_routine(t_collector clct, int elapse)
{
	int				elp;
	struct timeval	start;

	if (elapse > 0)
	{
		gettimeofday(&start, NULL);
		while (1)
		{
			elp = (int)get_elapsed(start);
			if (elp >= elapse)
				return (0);
			else if (elp >= clct.input->time_die)
			{
				put_fork_down(clct.table, clct.self, NULL, L_FORK);
				put_fork_down(clct.table, (clct.self + 1) % clct.input->philo_num, NULL, L_FORK);
				print_msg(clct.printer, clct.self, DEAD);
				return (1);
			}
			usleep(elapse);
		}
	}
	return (0);
}

long long	get_elapsed(struct timeval since)
{
	long long		elapsed;
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	elapsed = (cur.tv_sec * 1000 + cur.tv_usec / 1000) \
				- (since.tv_sec * 1000 + since.tv_usec / 1000);
	return (elapsed);
}
